
#include "language_record_initializer.h"

namespace match_stick
{

LanguageRecord LanguageRecordInitializer::Initialize()
{
    LanguageRecord record;

    //! @todo テキストの初期化をファイルから行うようにする．

    record.Set("title_button_to_game", LanguageRecord::Country::kJapan, "ゲームへ");
    record.Set("title_button_to_game", LanguageRecord::Country::kEnglish, "Start");

    record.Set("title_button_to_setting", LanguageRecord::Country::kJapan, "設定へ");
    record.Set("title_button_to_setting", LanguageRecord::Country::kEnglish, "Setting");


    record.Set("setting_button_to_title", LanguageRecord::Country::kJapan, "タイトルへ");
    record.Set("setting_button_to_title", LanguageRecord::Country::kEnglish, "Title");

    record.Set("setting_button_to_game_end", LanguageRecord::Country::kJapan, "ゲーム終了");
    record.Set("setting_button_to_game_end", LanguageRecord::Country::kEnglish, "Exit");

    return record;
}

} // namespace match_stick
