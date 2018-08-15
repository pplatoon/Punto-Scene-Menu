
// Include the only file
#include "CustomUI.h"

// Create two pages with their names
static CustomUI::Page page1("Main");
static CustomUI::Page page2("Homebrew");
static CustomUI::Page page3("About");

// Static var
static string text1 = "Menu";

// Rendering functions
void page1render()
{
    page1.renderText(text1", 20, 20, { 0, 0, 255, 255 }, 50);
}

void page2render()
{
    page1.renderText("WIP", 30, 30, { 255, 0, 255, 255 }, 50);
}

int main()
{
    // Init libs, with a title, a footer and a theme (you can create your own themes!)
    CustomUI::init("Punto Scene Menu", "Alpha", CustomUI::HorizonDark());

    // Set their rendering functions (what will be called every time the UI renders)
    page1.onRender(page1render);
    page2.onRender(page2render);

    // Add both pages to our UI
    CustomUI::addPage(page1);
    CustomUI::addPage(page2);
	CustomUI::addPage(page3);

    // Main loop starts
    while(appletMainLoop())
    {
        // Every main loop flushGraphics must be called
        CustomUI::flushGraphics();

        // This is the proper way to access input with CustomUI as every loop the keys are updated
        int keysDown = CustomUI::PressedInput;

        // If A is pressed...
        if(keysDown & KEY_A)
        {
            // We change the text
            text1 = "A pressed!";

            // Every time we change something affecting the render we should call this to redraw/re-render the UI
            CustomUI::renderGraphics();
        }
    }

    // With exitApp we don't need to call "return 0"
    CustomUI::exitApp();
}