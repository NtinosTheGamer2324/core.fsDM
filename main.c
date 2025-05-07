#include "FLEX-SYSTEM.h"
#include "FLEX-RENDERER.h"
#include "flexFAT.h"

int main() {
// Set background and mode
render_setbackimg(flex_fat("./bg.png"));
flex_setmode("GUI");

cpp
Copy
Edit
// Get users list
char** users = to_array(flex_getallusers());

// Create input fields
void* username_box = render_create_TEXTBOX("UserName: ");
void* password_box = render_create_TEXTBOX("Password: ");
render_spacer();

// Create buttons
void* login_btn = render_create_BUTTON("Login");
render_spacer();
render_text("OR");
render_spacer();
void* guest_btn = render_create_BUTTON("Continue as Guest");
render_text("(uses flex-session only!)");

// Main loop (pseudo)
while (1) {
    render_update(); // hypothetical function that checks GUI states

    if (render_button_pressed(login_btn)) {
        const char* username = render_get_TEXTBOX_value(username_box);
        const char* password = render_get_TEXTBOX_value(password_box);

        if (username_exists(users, username) &&
            strcmp(password, get_password_of(username)) == 0) {
            char command[256];
            snprintf(command, sizeof(command), "flex-session --%s --%s", username, password);
            system_runcommand(command);
            break;
        } else {
            system_saytext("Password OR User incorrect!");
        }
    }

    if (render_button_pressed(guest_btn)) {
        system_runcommand("flex-session --GUEST");
        break;
    }
}

return 0;
}
