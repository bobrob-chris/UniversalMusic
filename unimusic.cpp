/*******************************************************************************************
*
*   Main v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"
//absolutely essential that these go above the line "define raygui_implementation"
#include "player.h"
#include "config.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_dark.h"
#include "stdio.h"
#include "unimusic.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;



//----------------------------------------------------------------------------------
// Global Variables Declaration
//----------------------------------------------------------------------------------
Rectangle PanelRec;

vector<string> songs = {"Good Day-IU-4:00-https://www.youtube.com/watch?v=cRdvzzWIfkA", 
					   "Sunflower-Post Malone, Swae Lee-2:41-https://www.youtube.com/watch?v=ApXoWvfEYVU", 
					   "23-IU-3:14-https://www.youtube.com/watch?v=IbhWNjvh1u8", 
					   "Perfect Man-SHINHWA-3:25-https://www.youtube.com/watch?v=tccg1CeSCTU", 
					   "Run BTS-BTS-3:24-https://www.youtube.com/watch?v=a4YwJCZRh5M", 
					   "Fallin' (Adrenaline)-Why Don't We-3:33-https://www.youtube.com/watch?v=MU0BgB8N1B8", 
					   "Somebody That I Used To Know-Gotye (feat. Kimbra)-2:41-https://www.youtube.com/watch?v=ApXoWvfEYVU", 
					   "BIRDS OF A FEATHER-Billie Eilish-3:50-https://www.youtube.com/watch?v=V9PVRfjEBTI", 
					   "Summertime Sadness-PLana Del Rey-4:25-https://www.youtube.com/watch?v=ApXoWvfEYVU", 
					   "Sweater Weather-The Neighbourhood-4:13-https://www.youtube.com/watch?v=GCdwKhTtNNw&pp=0gcJCb4JAYcqIYzv", 
					   "Love Me Again-John Newman-3:56-https://www.youtube.com/watch?v=CfihYWRWRTQ", 
					   "blue-yung kai-3:42-https://www.youtube.com/watch?v=IpFX2vq8HKw", 
					   "Counting Stars-OneRepublic-4:43-https://www.youtube.com/watch?v=hT_nvWreIhg"};

string topDisplayText = "-----";

bool FilePressed = false;
bool EditPressed = false;
bool ImportPressed = false;
bool ViewPressed = false;
int f = -1;
int e = -1;
int i = -1;
int v = -1;

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------

    // backend
    UniMusic::MusicPlayer m = UniMusic::MusicPlayer(HIDDEN_SPOTIFY_CLIENT_ID,HIDDEN_SPOTIFY_CLIENT_SECRET, HIDDEN_YOUTUBE_API_KEY);
    m.setUp();

	// screen
	float sWidth = GetScreenWidth();
	float screenCenterX = sWidth / 2;
	float sHeight = GetScreenHeight();
	float screenWidth = 800;
    float screenHeight = 460;
	float leftMargin = 20;
	
	// tool bar
	float toolBarY = 20;
	float toolButtonW = 130;
	float toolButtonH = 45;
	const char* fileFunc = "File;Save;Save As;Open;Help;Exit";
	const char* editFunc = "Edit;Manually Change Playlist;Delete Playlist;Update Playlist";
	const char* importFunc = "Import;Import Playlist;Import User";
	const char* viewFunc = "View;User Info;Config";
	
	// Now Playing Text
	int displayTextFontSize = 23;
	float displayTextY = 85;

	// Music Queue
	int musicFontSize = 30;
	float musicHeight = 50;
	vector<bool> songsPressed(m.displayList.size());
	bool Playing = false;
	int currSong = -1;
	
	// Scroll Panel
	float scrollBoxY = 115;
	float maxWidth = 400;
	float contentHeight = musicHeight * m.displayList.size() + 20; // 20 for padding
	Rectangle PanelView = { 0, 0, 0, 0 };
    Vector2 PanelScrollOffset = { 0, 0 };
    Vector2 PanelBoundsOffset = { 0, 0 };
	PanelRec = Rectangle{ leftMargin, scrollBoxY, sWidth - PanelBoundsOffset.x - 50, sHeight - PanelBoundsOffset.y - 200};
	Rectangle PanelContent = Rectangle{ leftMargin, scrollBoxY, sWidth - PanelBoundsOffset.x - 80, contentHeight};

	// Bottom Functions
	bool PlayPressed = false;
	bool PausePressed = false;
	bool NextPressed = false;
	bool PrevPressed = false;
	
	// Initialize Window
    InitWindow(screenWidth, screenHeight, "Music App");
	
	// Set window and default style
	GuiLoadStyleDark();
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(screenWidth, screenHeight);
	int style = GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);
	GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, style+6);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
	GuiSetStyle(SCROLLBAR, ARROWS_VISIBLE, true);

    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
		screenCenterX = GetScreenWidth() / 2;
		sWidth = GetScreenWidth();
		sHeight = GetScreenHeight();
		PanelRec = Rectangle{ leftMargin, scrollBoxY, min(sWidth - PanelBoundsOffset.x - 50, maxWidth+30), sHeight - PanelBoundsOffset.y - 210};
		PanelContent = Rectangle{ leftMargin, scrollBoxY, min(sWidth - PanelBoundsOffset.x - 80, maxWidth), contentHeight};
		screenCenterX = min(static_cast<float>(GetScreenWidth() / 2), ((maxWidth+30)/2));
		
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

			DrawText(topDisplayText.c_str(), leftMargin, displayTextY, displayTextFontSize, GetColor(GuiGetStyle(DEFAULT, TEXT)));
			
			// scroll panel
 			GuiScrollPanel(PanelRec, NULL, PanelContent, &PanelScrollOffset, &PanelView);
            BeginScissorMode(PanelView.x, PanelView.y, PanelView.width, PanelView.height);
            
           

      
            for (int i = 0; i < m.displayList.size(); i++){
                string songText = ReplaceString(m.displayList[i], STANDARD_DELIMITER);

            /*
            for (float i = 0; i < songs.size(); i++) {
                const string del = "-";
                string songText = ReplaceString(songs[i], del);
            */
                float songWidth = songText.length() * 12.5;
                if (songWidth > maxWidth) maxWidth = songWidth + 10;
                Rectangle musicRec = { PanelRec.x + PanelScrollOffset.x, PanelRec.y + PanelScrollOffset.y + (musicHeight*i), PanelContent.width, musicHeight};
                bool temp = false;
                if (currSong == i) {
                    temp = true;
                }
                GuiMusicItem(musicRec, songText.c_str(), &temp, musicFontSize);
                if (temp == true && currSong != i) {
                    currSong = i;
                    Playing = false;
                    UpdateSongArtist(currSong, m.displayList);
                } else if (temp == false && currSong == i) {
                    Playing = false;
                    currSong = -1;
                    topDisplayText = "-----";
                }
            }
            
            
            
			EndScissorMode();

			// top bar
			if (FilePressed) GuiLock();
				if (GuiMenuDropdown(Rectangle{ leftMargin, toolBarY, toolButtonW, toolButtonH }, fileFunc, &f, FilePressed)){
					FilePressed = !FilePressed;
				}
            GuiUnlock();

			if (EditPressed) GuiLock();
				if (GuiMenuDropdown(Rectangle{ leftMargin + toolButtonW+10, toolBarY, toolButtonW, toolButtonH }, editFunc, &e, EditPressed)){
					EditPressed = !EditPressed;
				}
            GuiUnlock();
			
			if (ImportPressed) GuiLock();
				if (GuiMenuDropdown(Rectangle{ leftMargin + (toolButtonW+10)*2, toolBarY, toolButtonW, toolButtonH }, importFunc, &i, ImportPressed)){
					ImportPressed = !ImportPressed;
				}
            GuiUnlock();
			
			if (ViewPressed) GuiLock();
				if (GuiMenuDropdown(Rectangle{ leftMargin + (toolButtonW+10)*3, toolBarY, toolButtonW, toolButtonH }, viewFunc, &v, ViewPressed)){
					ViewPressed = !ViewPressed;
				}
            GuiUnlock();
			
			
			// open top tool bar models
			int result;			
			// File
			switch (f) {
			  case 1:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Save", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) f = -1;
				break;
			  case 2:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Save As", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) f = -1;
				break;
			  case 3:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Open", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) f = -1;
				break;
			  case 4:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Help", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) f = -1;
				break;
			  case 5:
				CloseWindow();
				return 0;
			}
			
			// Edit
			switch (e) {
			  case 1:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Manually Change Playlist", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) e = -1;
				break;
			  case 2:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Delete Playlist", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) e = -1;
				break;
			  case 3:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Update Playlist", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) e = -1;
				break;
			}
			
			// Import
			switch (i) {
			  case 1:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Import Playlist", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) i = -1;
				break;
			  case 2:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Import User", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) i = -1;
				break;
			}
			
			// View
			switch (v) {
			  case 1:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#User Info", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) v = -1;
				break;
			  case 2:
                result = GuiUtilityModal(Rectangle{ leftMargin, toolBarY, sWidth-90, sHeight-100 },
                    "#191#Config", "Hi! This is a message!", "Nice;Cool");
                if (result >= 0) v = -1;
				break;
			}
			
			// bottom buttons
			if (GuiButton(Rectangle{ screenCenterX-100, sHeight-70, 50, 50 }, GuiIconText(ICON_PLAYER_PREVIOUS, ""))) PrevPressed = true;
			if (PrevPressed) {
				if (currSong > 0 && Playing) {
					currSong -= 1;
					UpdateSongArtist(currSong, m.displayList);
					string first = "Now Playing: ";
					topDisplayText = first + topDisplayText;
				}
				PrevPressed = false;
			};
			if (GuiButton(Rectangle{ screenCenterX-50, sHeight-70, 50, 50 }, GuiIconText(ICON_PLAYER_PLAY, ""))) PlayPressed = true;
			if (PlayPressed) {
				if (!Playing && currSong != -1) {
					string first = "Now Playing: ";
					topDisplayText = first + topDisplayText;
					Playing = true;
				}
				PlayPressed = false;
			};
			if (GuiButton(Rectangle{ screenCenterX, sHeight-70, 50, 50 }, GuiIconText(ICON_PLAYER_PAUSE, ""))) PausePressed = true;
			if (PausePressed) {
				if (Playing) {
					topDisplayText = topDisplayText.substr(13);
					Playing = false;
				}
				PausePressed = false;
			};
			if (GuiButton(Rectangle{ screenCenterX+50, sHeight-70, 50, 50 }, GuiIconText(ICON_PLAYER_NEXT, ""))) NextPressed = true;
			if (NextPressed) {
				if (Playing && currSong < m.displayList.size()-1) {
					currSong += 1;
					UpdateSongArtist(currSong, m.displayList);
					string first = "Now Playing: ";
					topDisplayText = first + topDisplayText;
				}
				NextPressed = false;
			};
		
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    m.close();
    return 0;
}





//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

// Updates current song and artist text; should only be used when currSong gets updated
void UpdateSongArtist(int i, vector<string> list) {
	stringstream ss(list[i]);
	string title, artist;
	getline(ss, title, STANDARD_DELIMITER[0]);
	getline(ss, artist, STANDARD_DELIMITER[0]);
	string second = " by ";
	topDisplayText = title + second + artist;
}

string ReplaceString(string subject, const string& search) {
    size_t pos = 0;
	subject = " " + subject;
	pos = subject.find(search, pos);
	subject.replace(pos, search.length(), " - ");
	pos += 3;
	pos = subject.find(search, pos);
    if (pos != string::npos) {
        subject.replace(pos, search.length(), "..........[");
        subject.append("]");
        /*
        pos += 11;
        pos = subject.find(search, pos);
        subject.replace(pos, search.length(), "]  ");
        */
    }
	return subject;
}

// Modal for functions control; this is currently a generic message box, will need to be individually defined later :)
int GuiUtilityModal(Rectangle bounds, const char *title, const char *message, const char *buttons)
{
    #if !defined(RAYGUI_MESSAGEBOX_BUTTON_HEIGHT)
        #define RAYGUI_MESSAGEBOX_BUTTON_HEIGHT    24
    #endif
    #if !defined(RAYGUI_MESSAGEBOX_BUTTON_PADDING)
        #define RAYGUI_MESSAGEBOX_BUTTON_PADDING   12
    #endif

    int result = -1;    // Returns clicked button from buttons list, 0 refers to closed window button

    int buttonCount = 0;
    const char **buttonsText = GuiTextSplit(buttons, ';', &buttonCount, NULL);
    Rectangle buttonBounds = { 0 };
    buttonBounds.x = bounds.x + RAYGUI_MESSAGEBOX_BUTTON_PADDING;
    buttonBounds.y = bounds.y + bounds.height - RAYGUI_MESSAGEBOX_BUTTON_HEIGHT - RAYGUI_MESSAGEBOX_BUTTON_PADDING;
    buttonBounds.width = (bounds.width - RAYGUI_MESSAGEBOX_BUTTON_PADDING*(buttonCount + 1))/buttonCount;
    buttonBounds.height = RAYGUI_MESSAGEBOX_BUTTON_HEIGHT;

    //int textWidth = GetTextWidth(message) + 2;

    Rectangle textBounds = { 0 };
    textBounds.x = bounds.x + RAYGUI_MESSAGEBOX_BUTTON_PADDING;
    textBounds.y = bounds.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + RAYGUI_MESSAGEBOX_BUTTON_PADDING;
    textBounds.width = bounds.width - RAYGUI_MESSAGEBOX_BUTTON_PADDING*2;
    textBounds.height = bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - 3*RAYGUI_MESSAGEBOX_BUTTON_PADDING - RAYGUI_MESSAGEBOX_BUTTON_HEIGHT;

    // Draw control
    //--------------------------------------------------------------------
    if (GuiWindowBox(bounds, title)) result = 0;

    int prevTextAlignment = GuiGetStyle(LABEL, TEXT_ALIGNMENT);
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiLabel(textBounds, message);
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, prevTextAlignment);

    prevTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    for (int i = 0; i < buttonCount; i++)
    {
        if (GuiButton(buttonBounds, buttonsText[i])) result = i + 1;
        buttonBounds.x += (buttonBounds.width + RAYGUI_MESSAGEBOX_BUTTON_PADDING);
    }

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevTextAlignment);
    //--------------------------------------------------------------------

    return result;
}


// Music Item control, returns true when clicked
void GuiMusicItem(Rectangle bounds, const char *text, bool *active, int fontSize)
{
    GuiState state = guiState;

    bool temp = false;
    if (active == NULL) active = &temp;

    // Update control
    //--------------------------------------------------------------------
    if ((PanelRec.y < bounds.y + bounds.height/2) && (bounds.y + bounds.height/2 < PanelRec.y + PanelRec.height)
		&& (state != STATE_DISABLED) && !guiLocked && !guiControlExclusiveMode)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check toggle button state
        if (CheckCollisionPointRec(mousePoint, bounds) && !FilePressed && !EditPressed && !ImportPressed && !ViewPressed
			&& f == -1 && e == -1 && i == -1 && v == -1)
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                state = STATE_NORMAL;
                *active = !(*active);
            }
            else state = STATE_FOCUSED;
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    if (state == STATE_NORMAL)
    {
        GuiDrawRectangle(bounds, GuiGetStyle(TOGGLE, BORDER_WIDTH), GetColor(GuiGetStyle(TOGGLE, ((*active)? BORDER_COLOR_PRESSED : (BORDER + state*3)))), GetColor(GuiGetStyle(TOGGLE, ((*active)? BASE_COLOR_PRESSED : (BASE + state*3)))));
        CustomGuiDrawText(text, GetTextBounds(TOGGLE, bounds), TEXT_ALIGN_CENTER, GetColor(GuiGetStyle(TOGGLE, ((*active)? TEXT_COLOR_PRESSED : (TEXT + state*3)))), fontSize);
    }
    else
    {
        GuiDrawRectangle(bounds, GuiGetStyle(TOGGLE, BORDER_WIDTH), GetColor(GuiGetStyle(TOGGLE, BORDER + state*3)), GetColor(GuiGetStyle(TOGGLE, BASE + state*3)));
        CustomGuiDrawText(text, GetTextBounds(TOGGLE, bounds), TEXT_ALIGN_CENTER, GetColor(GuiGetStyle(TOGGLE, TEXT + state*3)), fontSize);
    }
    if (state == STATE_FOCUSED) GuiTooltip(bounds);

}

// handle dropdown menu functionalities
int GuiMenuDropdown(Rectangle bounds, const char *text, int *active, bool editMode)
{
    int result = 0;
    GuiState state = guiState;

    int temp = 0;
    if (active == NULL) active = &temp;
	
    int direction = 0; // Dropdown box open direction: down (default)
    if (GuiGetStyle(DROPDOWNBOX, DROPDOWN_ROLL_UP) == 1) direction = 1; // Up

    // Get substrings items from text (items pointers, lengths and count)
    int itemCount = 0;
    const char **items = GuiTextSplit(text, ';', &itemCount, NULL);

    int itemSelected = *active;
    int itemFocused = -1;
	int newWidth = bounds.width;
	// make box larger if necessary
	for (int i = 1; i < itemCount; i++) {
		string curr = items[i];
		float itemWidth = curr.length() * 20;
		if (itemWidth > bounds.width) newWidth = itemWidth;
	}
	
    Rectangle boundsOpen = bounds;
    boundsOpen.height = (itemCount)*(bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
    if (direction == 1) boundsOpen.y -= (itemCount-1)*(bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING)) + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING);
	
    Rectangle itemBounds = bounds;

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && (editMode || !guiLocked) && (itemCount > 1) && !guiControlExclusiveMode)
    {
        Vector2 mousePoint = GetMousePosition();

        if (editMode)
        {
            state = STATE_PRESSED;

            // Check if mouse has been pressed or released outside limits
            if (!CheckCollisionPointRec(mousePoint, boundsOpen))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) result = 1;
            }

            // Check if already selected item has been pressed again
            if (CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) result = 1;

            // Check focused and selected item
            for (int i = 1; i < itemCount; i++)
            {
                // Update item rectangle y position for next item
                if (direction == 0) {
					itemBounds.y += (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
					itemBounds.width = newWidth;
				}
                else itemBounds.y -= (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));

                if (CheckCollisionPointRec(mousePoint, itemBounds))
                {
                    itemFocused = i;
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        itemSelected = i;
                        result = 1;         // Item selected
                    }
                    break;
                }
            }

            itemBounds = bounds;
        }
        else
        {
            if (CheckCollisionPointRec(mousePoint, bounds) && f == -1 && e == -1 && i == -1 && v == -1)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    result = 1;
                    state = STATE_PRESSED;
                }
                else state = STATE_FOCUSED;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
	
	if (editMode){
		boundsOpen.width = newWidth;
		boundsOpen.y += (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
		boundsOpen.height -= (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
		GuiPanel(boundsOpen, NULL);
	}
	
    GuiDrawRectangle(bounds, GuiGetStyle(DROPDOWNBOX, BORDER_WIDTH), GetColor(GuiGetStyle(DROPDOWNBOX, BORDER + state*3)), GetColor(GuiGetStyle(DROPDOWNBOX, BASE + state*3)));
    GuiDrawText(items[0], GetTextBounds(DROPDOWNBOX, bounds), GuiGetStyle(DROPDOWNBOX, TEXT_ALIGNMENT), GetColor(GuiGetStyle(DROPDOWNBOX, TEXT + state*3)));

    if (editMode)
    {
        // Draw visible items
        for (int i = 1; i < itemCount; i++)
        {
            // Update item rectangle y position for next item
            if (direction == 0) {
				itemBounds.y += (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
				itemBounds.width = newWidth;
			}
            else itemBounds.y -= (bounds.height + GuiGetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING));
			
            if (i == itemFocused)
            {
                GuiDrawRectangle(itemBounds, GuiGetStyle(DROPDOWNBOX, BORDER_WIDTH), GetColor(GuiGetStyle(DROPDOWNBOX, BORDER_COLOR_FOCUSED)), GetColor(GuiGetStyle(DROPDOWNBOX, BASE_COLOR_FOCUSED)));
                GuiDrawText(items[i], GetTextBounds(DROPDOWNBOX, itemBounds), GuiGetStyle(DROPDOWNBOX, TEXT_ALIGNMENT), GetColor(GuiGetStyle(DROPDOWNBOX, TEXT_COLOR_FOCUSED)));
            }
            else GuiDrawText(items[i], GetTextBounds(DROPDOWNBOX, itemBounds), GuiGetStyle(DROPDOWNBOX, TEXT_ALIGNMENT), GetColor(GuiGetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL)));
        }
    }

    if (!GuiGetStyle(DROPDOWNBOX, DROPDOWN_ARROW_HIDDEN))
    {
        // Draw arrows (using icon if available)
#if defined(RAYGUI_NO_ICONS)
        GuiDrawText("v", RAYGUI_CLITERAL(Rectangle){ bounds.x + bounds.width - GuiGetStyle(DROPDOWNBOX, ARROW_PADDING), bounds.y + bounds.height/2 - 2, 10, 10 },
            TEXT_ALIGN_CENTER, GetColor(GuiGetStyle(DROPDOWNBOX, TEXT + (state*3))));
#else
        GuiDrawText(direction? "#121#" : "#120#", RAYGUI_CLITERAL(Rectangle){ bounds.x + bounds.width - GuiGetStyle(DROPDOWNBOX, ARROW_PADDING), bounds.y + bounds.height/2 - 6, 10, 10 },
            TEXT_ALIGN_CENTER, GetColor(GuiGetStyle(DROPDOWNBOX, TEXT + (state*3))));   // ICON_ARROW_DOWN_FILL
#endif
    }
    //--------------------------------------------------------------------

    *active = itemSelected;

    // TODO: Use result to return more internal states: mouse-press out-of-bounds, mouse-press over selected-item...
    return result;   // Mouse click: result = 1
}

// Same as GuiDrawText except it can take in a custom font size
static void CustomGuiDrawText(const char *text, Rectangle textBounds, int alignment, Color tint, int my_font_size)
{
    #define TEXT_VALIGN_PIXEL_OFFSET(h)  ((int)h%2)     // Vertical alignment for pixel perfect

    #if !defined(ICON_TEXT_PADDING)
        #define ICON_TEXT_PADDING   4
    #endif

    if ((text == NULL) || (text[0] == '\0')) return;    // Security check

    // PROCEDURE:
    //   - Text is processed line per line
    //   - For every line, horizontal alignment is defined
    //   - For all text, vertical alignment is defined (multiline text only)
    //   - For every line, wordwrap mode is checked (useful for GuitextBox(), read-only)

    // Get text lines (using '\n' as delimiter) to be processed individually
    // WARNING: We can't use GuiTextSplit() function because it can be already used
    // before the GuiDrawText() call and its buffer is static, it would be overriden :(
    int lineCount = 0;
    const char **lines = GetTextLines(text, &lineCount);

    // Text style variables
    //int alignment = GuiGetStyle(DEFAULT, TEXT_ALIGNMENT);
    int alignmentVertical = GuiGetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL);
    int wrapMode = GuiGetStyle(DEFAULT, TEXT_WRAP_MODE);    // Wrap-mode only available in read-only mode, no for text editing

    // TODO: WARNING: This totalHeight is not valid for vertical alignment in case of word-wrap
    float totalHeight = (float)(lineCount*my_font_size + (lineCount - 1)*my_font_size/2);
    float posOffsetY = 0.0f;

    for (int i = 0; i < lineCount; i++)
    {
        int iconId = 0;
        lines[i] = GetTextIcon(lines[i], &iconId);      // Check text for icon and move cursor

        // Get text position depending on alignment and iconId
        //---------------------------------------------------------------------------------
        Vector2 textBoundsPosition = { textBounds.x, textBounds.y };
        float textBoundsWidthOffset = 0.0f;

        // NOTE: We get text size after icon has been processed
        // WARNING: GetTextWidth() also processes text icon to get width! -> Really needed?
        int textSizeX = GetTextWidth(lines[i]);

        // If text requires an icon, add size to measure
        if (iconId >= 0)
        {
            textSizeX += RAYGUI_ICON_SIZE*guiIconScale;

            // WARNING: If only icon provided, text could be pointing to EOF character: '\0'
#if !defined(RAYGUI_NO_ICONS)
            if ((lines[i] != NULL) && (lines[i][0] != '\0')) textSizeX += ICON_TEXT_PADDING;
#endif
        }

        // Check guiTextAlign global variables
        switch (alignment)
        {
            case TEXT_ALIGN_LEFT: textBoundsPosition.x = textBounds.x; break;
            case TEXT_ALIGN_CENTER: textBoundsPosition.x = textBounds.x +  textBounds.width/2 - textSizeX/2; break;
            case TEXT_ALIGN_RIGHT: textBoundsPosition.x = textBounds.x + textBounds.width - textSizeX; break;
            default: break;
        }

        if (textSizeX > textBounds.width && (lines[i] != NULL) && (lines[i][0] != '\0')) textBoundsPosition.x = textBounds.x;

        switch (alignmentVertical)
        {
            // Only valid in case of wordWrap = 0;
            case TEXT_ALIGN_TOP: textBoundsPosition.y = textBounds.y + posOffsetY; break;
            case TEXT_ALIGN_MIDDLE: textBoundsPosition.y = textBounds.y + posOffsetY + textBounds.height/2 - totalHeight/2 + TEXT_VALIGN_PIXEL_OFFSET(textBounds.height); break;
            case TEXT_ALIGN_BOTTOM: textBoundsPosition.y = textBounds.y + posOffsetY + textBounds.height - totalHeight + TEXT_VALIGN_PIXEL_OFFSET(textBounds.height); break;
            default: break;
        }

        // NOTE: Make sure we get pixel-perfect coordinates,
        // In case of decimals we got weird text positioning
        textBoundsPosition.x = (float)((int)textBoundsPosition.x);
        textBoundsPosition.y = (float)((int)textBoundsPosition.y);
        //---------------------------------------------------------------------------------

        // Draw text (with icon if available)
        //---------------------------------------------------------------------------------
#if !defined(RAYGUI_NO_ICONS)
        if (iconId >= 0)
        {
            // NOTE: We consider icon height, probably different than text size
            GuiDrawIcon(iconId, (int)textBoundsPosition.x, (int)(textBounds.y + textBounds.height/2 - RAYGUI_ICON_SIZE*guiIconScale/2 + TEXT_VALIGN_PIXEL_OFFSET(textBounds.height)), guiIconScale, tint);
            textBoundsPosition.x += (float)(RAYGUI_ICON_SIZE*guiIconScale + ICON_TEXT_PADDING);
            textBoundsWidthOffset = (float)(RAYGUI_ICON_SIZE*guiIconScale + ICON_TEXT_PADDING);
        }
#endif
        // Get size in bytes of text,
        // considering end of line and line break
        int lineSize = 0;
        for (int c = 0; (lines[i][c] != '\0') && (lines[i][c] != '\n') && (lines[i][c] != '\r'); c++, lineSize++){ }
        float scaleFactor = (float)my_font_size/guiFont.baseSize;

        int lastSpaceIndex = 0;
        bool tempWrapCharMode = false;

        int textOffsetY = 0;
        float textOffsetX = 0.0f;
        float glyphWidth = 0;

        int ellipsisWidth = GetTextWidth("...");
        bool textOverflow = false;
        for (int c = 0, codepointSize = 0; c < lineSize; c += codepointSize)
        {
            int codepoint = GetCodepointNext(&lines[i][c], &codepointSize);
            int index = GetGlyphIndex(guiFont, codepoint);

            // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
            // but we need to draw all of the bad bytes using the '?' symbol moving one byte
            if (codepoint == 0x3f) codepointSize = 1; // TODO: Review not recognized codepoints size

            // Get glyph width to check if it goes out of bounds
            if (guiFont.glyphs[index].advanceX == 0) glyphWidth = ((float)guiFont.recs[index].width*scaleFactor);
            else glyphWidth = (float)guiFont.glyphs[index].advanceX*scaleFactor;

            // Wrap mode text measuring, to validate if
            // it can be drawn or a new line is required
            if (wrapMode == TEXT_WRAP_CHAR)
            {
                // Jump to next line if current character reach end of the box limits
                if ((textOffsetX + glyphWidth) > textBounds.width - textBoundsWidthOffset)
                {
                    textOffsetX = 0.0f;
                    textOffsetY += GuiGetStyle(DEFAULT, TEXT_LINE_SPACING);

                    if (tempWrapCharMode)   // Wrap at char level when too long words
                    {
                        wrapMode = TEXT_WRAP_WORD;
                        tempWrapCharMode = false;
                    }
                }
            }
            else if (wrapMode == TEXT_WRAP_WORD)
            {
                if (codepoint == 32) lastSpaceIndex = c;

                // Get width to next space in line
                int nextSpaceIndex = 0;
                float nextSpaceWidth = GetNextSpaceWidth(lines[i] + c, &nextSpaceIndex);

                int nextSpaceIndex2 = 0;
                float nextWordSize = GetNextSpaceWidth(lines[i] + lastSpaceIndex + 1, &nextSpaceIndex2);

                if (nextWordSize > textBounds.width - textBoundsWidthOffset)
                {
                    // Considering the case the next word is longer than bounds
                    tempWrapCharMode = true;
                    wrapMode = TEXT_WRAP_CHAR;
                }
                else if ((textOffsetX + nextSpaceWidth) > textBounds.width - textBoundsWidthOffset)
                {
                    textOffsetX = 0.0f;
                    textOffsetY += GuiGetStyle(DEFAULT, TEXT_LINE_SPACING);
                }
            }

            if (codepoint == '\n') break;   // WARNING: Lines are already processed manually, no need to keep drawing after this codepoint
            else
            {
                // TODO: There are multiple types of spaces in Unicode,
                // maybe it's a good idea to add support for more: http://jkorpela.fi/chars/spaces.html
                if ((codepoint != ' ') && (codepoint != '\t'))      // Do not draw codepoints with no glyph
                {
                    if (wrapMode == TEXT_WRAP_NONE)
                    {
                        // Draw only required text glyphs fitting the textBounds.width
                        if (textSizeX > textBounds.width)
                        {
                            if (textOffsetX <= (textBounds.width - glyphWidth - textBoundsWidthOffset - ellipsisWidth))
                            {
                                DrawTextCodepoint(guiFont, codepoint, RAYGUI_CLITERAL(Vector2){ textBoundsPosition.x + textOffsetX, textBoundsPosition.y + textOffsetY }, (float)my_font_size, GuiFade(tint, guiAlpha));
                            }
                            else if (!textOverflow)
                            {
                                textOverflow = true;

                                for (int j = 0; j < ellipsisWidth; j += ellipsisWidth/3)
                                {
                                    DrawTextCodepoint(guiFont, '.', RAYGUI_CLITERAL(Vector2){ textBoundsPosition.x + textOffsetX + j, textBoundsPosition.y + textOffsetY }, (float)my_font_size, GuiFade(tint, guiAlpha));
                                }
                            }
                        }
                        else
                        {
                            DrawTextCodepoint(guiFont, codepoint, RAYGUI_CLITERAL(Vector2){ textBoundsPosition.x + textOffsetX, textBoundsPosition.y + textOffsetY }, (float)my_font_size, GuiFade(tint, guiAlpha));
                        }
                    }
                    else if ((wrapMode == TEXT_WRAP_CHAR) || (wrapMode == TEXT_WRAP_WORD))
                    {
                        // Draw only glyphs inside the bounds
                        if ((textBoundsPosition.y + textOffsetY) <= (textBounds.y + textBounds.height - my_font_size))
                        {
                            DrawTextCodepoint(guiFont, codepoint, RAYGUI_CLITERAL(Vector2){ textBoundsPosition.x + textOffsetX, textBoundsPosition.y + textOffsetY }, (float)my_font_size, GuiFade(tint, guiAlpha));
                        }
                    }
                }

                if (guiFont.glyphs[index].advanceX == 0) textOffsetX += ((float)guiFont.recs[index].width*scaleFactor + (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
                else textOffsetX += ((float)guiFont.glyphs[index].advanceX*scaleFactor + (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
            }
        }

        if (wrapMode == TEXT_WRAP_NONE) posOffsetY += (float)GuiGetStyle(DEFAULT, TEXT_LINE_SPACING);
        else if ((wrapMode == TEXT_WRAP_CHAR) || (wrapMode == TEXT_WRAP_WORD)) posOffsetY += (textOffsetY + (float)GuiGetStyle(DEFAULT, TEXT_LINE_SPACING));
        //---------------------------------------------------------------------------------
    }

#if defined(RAYGUI_DEBUG_TEXT_BOUNDS)
    GuiDrawRectangle(textBounds, 0, WHITE, Fade(BLUE, 0.4f));
#endif
}


