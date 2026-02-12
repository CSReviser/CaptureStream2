// constants_programs.h
#pragma once
#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStringList>
#include <QVector>

namespace Constants {

struct ProgramDefinition {
    enum class Kind { English, Optional, Spec, Feature };
    Kind kind;
    const char* keyChecked;
    bool checkedDefault;
    const char* keyId;
    const char* idDefault;
    bool saveId;
    bool hasId; 
    const char* keyLabel;
    const char* labelDefault;
    bool saveLabel;
    bool hasLabel; 
    const char* objectName;
};

// --- 配列の宣言（実体は.cpp） ---
extern const ProgramDefinition EnglishPrograms[];
extern const int EnglishCount;

extern const ProgramDefinition OptionalPrograms[];
extern const int OptionalCount;

extern const ProgramDefinition SpecPrograms[];
extern const int SpecCount;

// --- コンテナ系の取得関数 ---
const QMap<QString, QString>& getMap();
const QMultiMap<QString, QString>& getMultiMap();
const QMultiMap<QString, QString>& getMultiMap1();
const QVector<QStringList>& getOptPresets();
const QVector<QStringList>& getPresets();
const QStringList& getCourses();

// --- その他の構造体 ---
struct Item { const QString key; const char* defaultValue; };
extern const Item TITLE_ITEMS[];
extern const Item FILENAME_ITEMS[];
extern const int ITEM_COUNT;

struct CustomizePreset { const char* value; const char* label; };
extern const CustomizePreset FILENAME_PRESETS[];
extern const int FILENAME_PRESET_COUNT;
extern const CustomizePreset TITLE_PRESETS[];
extern const int TITLE_PRESETS_COUNT;

// 固定文字列は利便性のため inline のまま維持（変更頻度が低いため）
inline constexpr auto prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
inline constexpr auto suffix = "listdataflv.xml";
inline constexpr auto json_prefix = "https://www.nhk.or.jp/radioondemand/json/";


namespace Constants {
    // 構造体定義はそのまま
    struct ProgramDefinition { ... };

    // --- 実体配列の参照宣言 ---
    extern const ProgramDefinition EnglishPrograms[];
    extern const ProgramDefinition OptionalPrograms[];
    extern const ProgramDefinition SpecPrograms[];

    // --- 【重要】個数を自動で返す関数 ---
    int getEnglishCount();
    int getOptionalCount();
    int getSpecCount();
    int getItemCount();
    
    // std::array の代わりに使う側のための別名（セマンティクス維持）
    inline int getOptPresetSize() { return getOptionalCount(); }
    inline int getPresetSize() { return getSpecCount(); }

    // MapやVectorの取得関数（以前の提案通り）
    const QMap<QString, QString>& getMap();
}



} // namespace Constants





/*
#pragma once
#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStringList>
#include <QVector>

namespace Constants {

/*
 * ProgramDefinition
 * ------------------------------------------------------------
 * English / Optional / Spec / Feature をすべて統合した構造体。
 *
 * 目的：
 *   - 設定方法が異なる4種類のボタンを、最終的に一元データとして扱う
 *   - constants.h の定義を一本化し、同期ズレを防ぐ
 *
 * 各種別の意味：
 *   English : 固定番組（id/label が固定、checked のみ INI 保存）
 *   Optional: 任意設定番組（checked/id/label を INI 保存）
 *   Spec    : Optional と同じだが UI 上は別カテゴリ
 *   Feature : チェックボックス、コンボボックスの各種設定
 *   チェックボックス、コンボボックスの区別は
 *   objectNameに下記文字列を含むことで識別可能
 *   toolButton : コンボボックス
 *   checkBox   : チェックボックス、コンボボックス
 *
 * 空文字("") の扱い：
 *   - English の keyId/keyLabel は空（固定値なので保存不要）
 *   - Feature の id/label は空（番組IDを持たない）
 */
 /*
struct ProgramDefinition {
    enum class Kind {
        English,   // 固定番組
        Optional,  // 任意設定番組
        Spec,      // 特番
        Feature    // チェックボックス
    };

    Kind kind;

    // checked の保存キーとデフォルト値
    const char* keyChecked;
    bool    checkedDefault;

    // id の保存キーとデフォルト値（English/Feature は空）
    const char* keyId;
    const char* idDefault;
    bool    	saveId;
    bool    	hasId; 

    // label の保存キーとデフォルト値（English は固定値、Feature は空）
    const char* keyLabel;
    const char* labelDefault;
    bool    	saveLabel;
    bool    	hasLabel; 

    // UI の objectName（Feature で空の場合もある）
    const char* objectName;
};

/* ============================================================
 * English（固定番組）
 * ========================================================== */
//extern const ProgramDefinition EnglishPrograms[];
// ===== 固定の講座番組 カテゴリの数 =====
//extern const int EnglishCount;

/* ============================================================
 * English（固定番組）
 * ------------------------------------------------------------
 * id/label は固定値で、INI に保存されるのは checked のみ。
 * keyId/keyLabel は空文字でよい。
 * ========================================================== */
 /*
inline const ProgramDefinition EnglishPrograms[] = {
    { ProgramDefinition::Kind::English,
      "basic0", false,
      "basic0_keyId", "GGQY3M1929_01", false, true,
      "basic0_keyLabel", "小学生の基礎英語", false, true,
      "toolButton_basic0" },

    { ProgramDefinition::Kind::English,
      "basic1", false,
      "basic1_keyId", "148W8XX226_01", false, true,
      "basic1_keyLabel", "中学生の基礎英語 【レベル１】", false, true,
      "toolButton_basic1" },

    { ProgramDefinition::Kind::English,
      "basic2", false,
      "basic2_keyId", "83RW6PK3GG_01", false, true,
      "basic2_keyLabel", "中学生の基礎英語 【レベル２】", false, true,
      "toolButton_basic2" },

    { ProgramDefinition::Kind::English,
      "kaiwa", false,
      "kaiwa_keyId", "PMMJ59J6N2_01", false, true,
      "kaiwa_keyLabel", "ラジオ英会話", false, true,
      "toolButton_kaiwa" },

    { ProgramDefinition::Kind::English,
      "enjoy", false,
      "enjoy_keyId", "BR8Z3NX7XM_01", false, true,
      "enjoy_keyLabel", "エンジョイ・シンプル・イングリッシュ", false, true,
      "toolButton_enjoy" },

    { ProgramDefinition::Kind::English,
      "timetrial", false,
      "timetrial_keyId", "8Z6XJ6J415_01", false, true,
      "timetrial_keyLabel", "英会話タイムトライアル", false, true,
      "toolButton_timetrial" },

    { ProgramDefinition::Kind::English,
      "business1", false,
      "business1_keyId", "368315KKP8_01", false, true,
      "business1_keyLabel", "ラジオビジネス英語", false, true,
      "toolButton_business1" },

    { ProgramDefinition::Kind::English,
      "gendai", false,
      "gendai_keyId", "77RQWQX1L6_01", false, true,
      "gendai_keyLabel", "ニュースで学ぶ「現代英語」", false, true,
      "toolButton_gendai" }
};

    // ===== 固定の講座番組 カテゴリの数 =====
inline constexpr int  EnglishCount =
    sizeof(EnglishPrograms) / sizeof(EnglishPrograms[0]);

/* ============================================================
 * Optional（任意設定番組）
 * ========================================================== */
//extern const ProgramDefinition OptionalPrograms[];
// ===== 任意設定の講座番組 カテゴリの数 =====
//extern const int OptionalCount;

/* ============================================================
 * Optional（任意設定番組）
 * ------------------------------------------------------------
 * checked / id / label の3つを INI に保存する。
 * ========================================================== */
 /*
inline  const ProgramDefinition OptionalPrograms[] = {
    { ProgramDefinition::Kind::Optional,
      "optional_1", false,
      "optional1", "XQ487ZM61K_01", true, true,
      "opt_title1", "まいにちフランス語", true, true,
      "toolButton_optional1" },

    { ProgramDefinition::Kind::Optional,
      "optional_2", false,
      "optional2", "N8PZRZ9WQY_01", true, true,
      "opt_title2", "まいにちドイツ語", true, true,
      "toolButton_optional2" },

    { ProgramDefinition::Kind::Optional,
      "optional_3", false,
      "optional3", "LJWZP7XVMX_01", true, true,
      "opt_title3", "まいにちイタリア語", true, true,
      "toolButton_optional3" },

    { ProgramDefinition::Kind::Optional,
      "optional_4", false,
      "optional4", "NRZWXVGQ19_01", true, true,
      "opt_title4", "まいにちスペイン語", true, true,
      "toolButton_optional4" },

    { ProgramDefinition::Kind::Optional,
      "optional_5", false,
      "optional5", "YRLK72JZ7Q_01", true, true,
      "opt_title5", "まいにちロシア語", true, true,
      "toolButton_optional5" },

    { ProgramDefinition::Kind::Optional,
      "optional_6", false,
      "optional6", "N13V9K157Y_01", true, true,
      "opt_title6", "ポルトガル語", true, true,
      "toolButton_optional6" },

    { ProgramDefinition::Kind::Optional,
      "optional_7", false,
      "optional7", "983PKQPYN7_01", true, true,
      "opt_title7", "まいにち中国語", true, true,
      "toolButton_optional7" },

    { ProgramDefinition::Kind::Optional,
      "optional_8", false,
      "optional8", "LR47WW9K14_01", true, true,
      "opt_title8", "まいにちハングル講座", true, true,
      "toolButton_optional8" }
};
    // ===== 任意設定の講座番組 カテゴリの数 =====
inline constexpr int OptionalCount = std::size(EnglishPrograms);
//    sizeof(OptionalPrograms) / sizeof(OptionalPrograms[0]);

/* ============================================================
 * Spec（特番）
 * ========================================================== */
//extern const ProgramDefinition SpecPrograms[];
// ===== 任意設定の講座番組 カテゴリの数 =====
//extern const int SpecCount;
/* ============================================================
 * Spec（特番）
 * ------------------------------------------------------------
 * Optional と同じ構造だが UI 上は別カテゴリ。
 * ========================================================== */
 /*
inline  const ProgramDefinition SpecPrograms[] = {
    { ProgramDefinition::Kind::Spec,
      "special_1", false,
      "special1", "6LPPKP6W8Q_01", true, true,
      "spec_title1", "やさしい日本語", true, true,
      "toolButton_special1" },

    { ProgramDefinition::Kind::Spec,
      "special_2", false,
      "special2", "WKMNWGMN6R_01", true, true,
      "spec_title2", "アラビア語講座", true, true,
      "toolButton_special2" },

    { ProgramDefinition::Kind::Spec,
      "special_3", false,
      "special3", "GLZQ4M519X_01", true, true,
      "spec_title3", "Asian View", true, true,
      "toolButton_special3" },

    { ProgramDefinition::Kind::Spec,
      "special_4", false,
      "special4", "4MY6Q8XP88_01", true, true,
      "spec_title4", "Living in Japan", true, true,
      "toolButton_special4" }
};
    // ===== 任意設定の講座番組 カテゴリの数 =====
inline constexpr int SpecCount =
    sizeof(SpecPrograms) / sizeof(SpecPrograms[0]);

    // ===== 固定の URL などがある場合はここに追加 =====
    // inline constexpr auto BaseApiUrl = "https://example.com/api/";
    inline constexpr auto  prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
    inline constexpr auto  suffix = "listdataflv.xml";
    inline constexpr auto  json_prefix = "https://www.nhk.or.jp/radioondemand/json/";   
    
     // ===== 講座番組ID =====   
   inline const QMap<QString, QString> map = { 
         { "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
         { "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
         { "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
         { "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
         { "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
         { "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
         { "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
         { "77RQWQX1L6_01", "english/gendaieigo" },	// ニュースで学ぶ「現代英語」
         { "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
         { "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
         { "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
         { "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
         { "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
         { "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
         { "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
         { "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
         { "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
         { "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
         { "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
         { "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
         { "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
         { "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
         { "XQ487ZM61K_01", "french/kouza3" },		// まいにちフランス語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza3" },		// まいにちドイツ語 入門編/初級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza3" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza3" },		// まいにちイタリア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza3" },		// まいにちロシア語 入門編/初級編/応用編
         { "983PKQPYN7_s1", "chinese/kouza4" },		// まいにち中国語
         { "LR47WW9K14_s1", "hangeul/kouza4" },		// まいにちハングル講座
};

     // ===== 講座番組ID 分離ID(_x1、_y1) =====   	
   inline const QMultiMap<QString, QString> multimap = { 
         { "77RQWQX1L6_01", "english/gendaieigo" },	// ニュースで学ぶ「現代英語」
         { "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
         { "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
         { "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
         { "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
         { "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
         { "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
         { "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
         { "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
         { "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
         { "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
         { "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
         { "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
         { "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
         { "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
         { "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
         { "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
         { "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
         { "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
         { "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
         { "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
         { "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
         { "XQ487ZM61K_01", "french/kouza" },		// まいにちフランス語 入門編/初級編/応用編
         { "XQ487ZM61K_01", "french/kouza2" },		// まいにちフランス語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza" },		// まいにちドイツ語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza2" },		// まいにちドイツ語 入門編/初級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza2" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza" },		// まいにちイタリア語 入門編/初級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza2" },		// まいにちイタリア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza" },		// まいにちロシア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza2" },		// まいにちロシア語 入門編/初級編/応用編
         { "983PKQPYN7_s1", "chinese/kouza" },		// まいにち中国語
         { "LR47WW9K14_s1", "hangeul/kouza" },		// まいにちハングル講座
};	

     // ===== 講座番組ID 複合ID(_s1) =====  
   inline const QMultiMap<QString, QString> multimap1 = { 
         { "983PKQPYN7_s1", "983PKQPYN7_01" },		// まいにち中国語
         { "LR47WW9K14_s1", "LR47WW9K14_01" },		// まいにちハングル講座
         { "6LPPKP6W8Q_s1", "6LPPKP6W8Q_01" },		// やさしい日本語
         { "6LPPKP6W8Q_s1", "D6RM27PGVM_01" },		// Learn Japanese from the News
         { "6LPPKP6W8Q_s1", "4MY6Q8XP88_01" },		// Living in Japan
};	
 

    // ===== 任意設定の講座番組 プリセット値 =====
// 1セットは常に8つ
    inline constexpr std::size_t OPT_PRESET_SIZE = OptionalCount;

// プリセットは増減可能（行を増やすだけでOK）
inline const QVector<QStringList> OPT_PRESETS = {
    { "XQ487ZM61K_x1", "XQ487ZM61K_y1", "N8PZRZ9WQY_x1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_x1", "LJWZP7XVMX_y1", "NRZWXVGQ19_x1", "NRZWXVGQ19_y1" },
 //まいにちフランス語 入門編, //まいにちフランス語 応用編, //まいにちドイツ語 入門編／初級編, //まいにちドイツ語 応用編, //まいにちイタリア語 入門編, //まいにちイタリア語 応用編, //まいにちスペイン語 入門編／初級編 //まいにちスペイン語 中級編／応用編   
    { "983PKQPYN7_01", "GLZQ4M519X_01", "LR47WW9K14_01", "6LPPKP6W8Q_01", "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "WKMNWGMN6R_01", "N13V9K157Y_01" },
//まいにち中国語, //Asian View, //まいにちハングル講座, //やさしい日本語, //まいにちロシア語 入門編, //まいにちロシア語 応用編, //アラビア語講座  //ポルトガル語
    { "XQ487ZM61K_x1", "N8PZRZ9WQY_x1", "LJWZP7XVMX_x1", "NRZWXVGQ19_x1", "YRLK72JZ7Q_x1", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語 入門編, //まいにちドイツ語 入門編／初級編, //まいにちイタリア語 入門編, //まいにちスペイン語 入門編／初級編, //まいにちロシア語 入門編, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "XQ487ZM61K_y1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_y1", "NRZWXVGQ19_y1", "YRLK72JZ7Q_y1", "N13V9K157Y_01", "GLZQ4M519X_01", "WKMNWGMN6R_01" },
//まいにちフランス語 応用編, //まいにちドイツ語 応用編, //まいにちイタリア語 応用編, //まいにちスペイン語 中級編／応用編, //まいにちロシア語 応用編, //ポルトガル語, //Asian View  //アラビア語講座
    { "XQ487ZM61K_01", "N8PZRZ9WQY_01", "LJWZP7XVMX_01", "NRZWXVGQ19_01", "YRLK72JZ7Q_01", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語, //まいにちドイツ語, //まいにちイタリア語, //まいにちスペイン語, //まいにちロシア語, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "4MY6Q8XP88_01", "GLZQ4M519X_01", "6LPPKP6W8Q_01", "YR96XR51MZ_01", "X4X6N1XG8Z_01", "D85RZVGX7W_01", "LRK2VXPK5X_01", "M65G6QLKMY_01" },
//Living in Japan, //Asian View, //やさしい日本語, //朗読の世界, //青春アドベンチャー, //新日曜名作座, //朗読  //FMシアター 
    { "R5XR783QK3_01", "NJZR87XYYV_01", "5L3859P515_01", "566V9ZMX35_01", "YR96XR51MZ_01", "X78J5NKWM9_01", "MVYJ6PRZMX_01", "JWQ88ZVWQK_01" }
//おしゃべりな古典教室, //日曜カルチャー, //古典講読 //日曜討論, //朗読の世界 //こころをよむ, //アナウンサー百年百話  //宗教の時間
};

    // ===== 特番 プリセット値 =====
// 1セットは常に4つ
    inline constexpr std::size_t PRESET_SIZE = SpecCount;

// プリセットは増減可能（行を増やすだけでOK）
inline const QVector<QStringList> PRESETS = {
    { "6LPPKP6W8Q_01", "WKMNWGMN6R_01", "GLZQ4M519X_01", "4MY6Q8XP88_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "983PKQPYN7_01", "LR47WW9K14_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "983PKQPYN7_01", "LR47WW9K14_01", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "GLZQ4M519X_01", "X7R2P2PW5P_02", "L6ZQ2NX1NL_01", "34PY344RPJ_01" },
    { "X4X6N1XG8Z_01", "D85RZVGX7W_01", "YR96XR51MZ_01", "M65G6QLKMY_01" },
    { "R5XR783QK3_01", "X78J5NKWM9_01", "5L3859P515_01", "JWQ88ZVWQK_01" }
};

// FILE NAME、TITLEのkey/デフォルト値
struct Item {
    const QString key;
    const char* defaultValue;
};

inline const Item TITLE_ITEMS[] = {
    { KEY_CUSTOMIZED_TITLE1, "%f" },
    { KEY_CUSTOMIZED_TITLE2, "%k_%Y_%M_%D" }
};

inline const Item FILENAME_ITEMS[] = {
    { KEY_CUSTOMIZED_FILENAME1, "%k_%Y_%M_%D" },
    { KEY_CUSTOMIZED_FILENAME2, "%k_%Y_%M_%D" }
};

inline const int ITEM_COUNT = std::size(FILENAME_ITEMS);

    inline const QStringList COURSES = {
        QStringLiteral("json"),
        QStringLiteral("xml")
    };

    // FILE NAME、TITLEのプリセット（UI ラジオボタン用）
struct CustomizePreset {
    const char* value;
    const char* label;   // UI に表示する名前（必要なら）
};

inline const CustomizePreset FILENAME_PRESETS[] = {
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};

inline constexpr int FILENAME_PRESET_COUNT = std::size(FILENAME_PRESETS);


    // TITLEのプリセット（UI ラジオボタン用）
inline const CustomizePreset TITLE_PRESETS[] = {
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};

inline constexpr int TITLE_PRESETS_COUNT = std::size(TITLE_PRESETS);

}
*/
