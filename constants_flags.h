// constants_flags.h
#pragma once
namespace Constants {

/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ------------------------------------------------------------
 * ini ファイルに保存されない RuntimeConfig で使用する Flag。
 * RuntimeConfig 生成時に default で初期化され、
 * Settings / GUI / CLI によって上書きされる。
 * Feature と重複する場合は後からの値が優先される。
 * ========================================================== */      
   struct FlagEntry {
    const char* keyFlag;	// "nogui" など
    bool flagDefault;		// 初期値
};



inline const FlagEntry FlagTable[] = {
    { KEY_NOGUI, 	false },	// CLI: -nogui = true
    { KEY_LAST_WEEK, 	false },	// [前週]チェック = true
    { KEY_BOTH_WEEKS, 	false },	// CLI: -b = true
    { KEY_PROGRAM_LIST, false },	// 番組一覧表示 = true
    { "featureX",  true  } 	// ini に保存される Feature でもよい
}; 
     // ===== フラグの数 =====
constexpr int FlagCount = std::size(FlagTable);   

}
