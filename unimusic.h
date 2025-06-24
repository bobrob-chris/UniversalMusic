#ifndef ___UNIMUSIC__H_
#define ___UNIMUSIC__H_
#include <string>
#include <vector>

void UpdateSongArtist(int i, std::vector<std::string> list);
void GuiMusicItem(Rectangle bounds, const char *text, bool *active, int fontSize);
int GuiMenuDropdown(Rectangle bounds, const char *text, int *active, bool editMode);
int GuiUtilityModal(Rectangle bounds, const char *title, const char *message, const char *buttons);
std::string ReplaceString(std::string subject, const std::string& search);
static void CustomGuiDrawText(const char *text, Rectangle textBounds, int alignment, Color tint, int my_font_size);

#endif // MUSIC_H_
