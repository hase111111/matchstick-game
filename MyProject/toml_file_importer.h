﻿
#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "dxlib_debug_print.h"
#include "implicit_metafunction_for_toml11.h"
#include "interface_toml_data_validator.h"
#include "toml_data_validator_always_true.h"
#include "toml_file_exporter.h"


namespace match_stick {

//! @brief FromTomlを持つか判定するコンセプト．
//! @n toml::from<T>::from_toml()が定義されているかどうかを判定する．
//! @n また，デフォルトコンストラクタが実装されているかどうかも判定する．
template <typename T>
concept HasFromToml = std::is_default_constructible_v<T> && impl::has_from_toml<T>::value;


//! @class TomlFileImporter
//! @brief tomlファイルを読み込んで構造体に変換するテンプレートクラス．
//! @tparam T 変換先の構造体．デフォルトコンストラクタが実装されていること．
//! toml::from<T>()が定義されている必要がある．
template <HasFromToml T>
class TomlFileImporter final {
public:
    TomlFileImporter() : validator_(std::make_unique<TomlDataValidatorAlwaysTrue<T>>()) {}

    explicit TomlFileImporter(std::unique_ptr<ITomlDataValidator<T>>&& validator) : validator_(std::move(validator)) {}


    //! @brief 指定したファイルパスのファイルを読み込み，構造体に変換する．
    //! @param file_path 読み込むファイルのパス．
    //! @return 読み込んだ構造体．失敗した場合は std::nulloptを返す．
    std::optional<T> Import(const std::string& file_path) const {
        if (!FileIsExist(file_path)) { return std::nullopt; }

        toml::value toml_value;

        if (!ParseTomlFile(file_path, &toml_value)) { return std::nullopt; }

        T data;

        if (!SerializeTomlData(&toml_value, &data)) { return std::nullopt; }

        if (!ValidateData(data)) { return std::nullopt; }

        DEBUG_PRINT_INFO("Loading completed successfully.");

        return data;
    }

    //! @brief 指定したファイルパスのファイルを読み込み，構造体に変換する．
    //! 読込に失敗した場合は，デフォルトの構造体を返す．
    //! また，読込に失敗した場合には，
    //! デフォルトの構造体をファイルに出力するかどうかをユーザに問う．
    //! @param file_path 読み込むファイルのパス．
    //! @return 読み込んだ構造体．
    T ImportOrUseDefault(const std::string& file_path) const {
        const auto data = Import(file_path);

        if (data.has_value()) { return data.value(); }

        TomlFileExporter<T> exporter;
        exporter.Export(file_path, T());

        DEBUG_PRINT_WARNING("Use default data.");

        return T();
    }

private:
    bool FileIsExist(const std::string& file_path) const {
        if (!std::filesystem::exists(file_path)) {
            DEBUG_PRINT_ERROR("The file does not exist.");

            return false;
        }

        return true;
    }

    bool ParseTomlFile(const std::string& file_path, toml::value* toml_value) const {
        try {
            // バイナリモードで読み込む．
            std::ifstream ifs(file_path, std::ios::binary);

            *toml_value = toml::parse(ifs, file_path);
        } catch (toml::syntax_error err) {
            DEBUG_PRINT_ERROR("File parsing failed.");
            DEBUG_PRINT_ERROR("< Rows that failed to parse >");
            DEBUG_PRINT_ERROR(err.what());

            return false;
        }

        return true;
    }

    bool SerializeTomlData(toml::value* toml_value, T* data) const {
        try {
            *data = toml::from<T>::from_toml(*toml_value);
        } catch (...) {
            DEBUG_PRINT_ERROR("Data serialization failed.");

            return false;
        }

        return true;
    }

    bool ValidateData(const T& data) const {
        const auto [is_valid, error_message] = validator_->Validate(data);

        if (!is_valid) {
            DEBUG_PRINT_ERROR("Data validation failed.");
            DEBUG_PRINT_ERROR("<Reasons for Failure to Verify>");
            DEBUG_PRINT_ERROR(error_message);

            return false;
        }

        return true;
    }

    const std::unique_ptr<ITomlDataValidator<T>> validator_;
};

}  // namespace match_stick
