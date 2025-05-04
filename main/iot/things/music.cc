#include "iot/thing.h"
#include "board.h"
#include "display/lcd_display.h"
#include "settings.h"

#include <esp_log.h>
#include <string>

#define TAG "Music"

namespace iot
{

    // 这里仅定义 Music 的属性和方法，不包含具体的实现
    class Music : public Thing
    {
    private:
        // 配置相关
        std::string SEARCH_URL = "http://search.kuwo.cn/r.s";
        std::string PLAY_URL = "http://api.xiaodaokg.com/kuwo.php";
        std::string LYRIC_URL = "http://m.kuwo.cn/newh5/singles/songinfoandlrc";
        std::string USER_AGENT = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";
        std::string REFERER = "http://kuwo.cn/";

        // 搜索结果相关属性
        std::string current_song = ""; // 当前歌曲名称
        std::string current_url = ""; // 当前歌曲播放链接
        std::string song_id = ""; // 当前歌曲ID
        int total_duration = 0; // 歌曲总时长（秒）

        // 播放控制相关属性
        bool is_playing = false; // 是否正在播放
        bool paused = false; // 是否暂停
        int current_position = 0; // 当前播放位置（秒）
        int start_play_time = 0; // 开始播放的时间点

        // TTS相关属性
        bool paused_for_tts = false; // 是否因为TTS而暂停
        int pause_start_time = 0; // 暂停开始时间
        int total_pause_time = 0; // 总暂停时间

        // 歌词相关属性
        std::vector<std::pair<int, std::string>> lyrics;
        int current_lyric_index = 0; // 当前歌词索引
    public:
        Music() : Thing("Music", "在线音乐播放器，支持音乐搜索、本地缓存、播放控制和歌词显示，播放音乐时优先使用iot的音乐播放器")
        {
            properties_.AddStringProperty("current_song", "当前歌曲", [this]() -> std::string {
                return current_song;
            });
            properties_.AddBooleanProperty("is_playing", "是否正在播放", [this]() -> bool {
                return is_playing;
            });
            properties_.AddBooleanProperty("paused", "是否暂停", [this]() -> bool {
                return paused;
            });
            properties_.AddNumberProperty("total_duration", "歌曲总时长（秒）", [this]() -> int {
                return total_duration;
            });
            properties_.AddNumberProperty("current_position", "当前播放位置（秒）", [this]() -> int {
                return 0;
            });
            properties_.AddNumberProperty("progress", "播放进度（百分比）", [this]() -> int {
                return 0;
            });
            methods_.AddMethod(
                "SearchPlay",
                "搜索并播放指定歌曲",
                ParameterList({Parameter("song_name", "输入歌曲名称", kValueTypeString, true)}),
                [this](const ParameterList &parameters) {

                });
            methods_.AddMethod(
                "SearchSong",
                "仅搜索歌曲不播放",
                ParameterList({Parameter("song_name", "输入歌曲名称", kValueTypeString, true)}),
                [this](const ParameterList &parameters) {

                });
            methods_.AddMethod(
                "PlayPause",
                "播放/暂停切换",
                ParameterList(),
                [this](const ParameterList &parameters) {

                });
            methods_.AddMethod(
                "Stop",
                "停止播放",
                ParameterList(),
                [this](const ParameterList &parameters) {

                });
            methods_.AddMethod(
                "Seek",
                "跳转到指定位置",
                ParameterList({Parameter("position_seconds", "跳转位置（秒）", kValueTypeString, true)}),
                [this](const ParameterList &parameters) {

                });
            methods_.AddMethod(
                "GetLyrics",
                "获取当前歌曲歌词",
                ParameterList(),
                [this](const ParameterList &parameters) {

                });
        }
    };

} // namespace iot

DECLARE_THING(Music);