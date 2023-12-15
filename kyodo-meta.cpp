#include <gtk/gtk.h>
#include <json/json.h>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <string>

#include "icon.xpm"

// Global pointers for GTK widgets
GtkWidget* window;
GtkWidget* imagePathEntry;

// Kyodo News
GtkWidget* kyodoCheckbox;
GtkWidget* englishRadioButton;
GtkWidget* japaneseRadioButton;
GtkWidget* englishNumberEntry;
GtkWidget* japaneseNumberEntry;

GtkWidget* morningRadioButton;
GtkWidget* eveningRadioButton;

GtkWidget* sportsCheckbox;

// Kyodo Furusato
GtkWidget* furusatoCheckbox;
GtkWidget* furusatoNumberEntry;

// Navigation Report
GtkWidget* navreportCheckbox;
GtkWidget* navreportFromNumberEntry;
GtkWidget* navreportToNumberEntry;
GtkWidget* navreportToCheckbox;

// Kaiun-Suisan
GtkWidget* kaiunsuisanCheckbox;
GtkWidget* kaiunsuisanNumberEntry;

// Ocean Current Forecastings
GtkWidget* oceancurrentCheckbox;
GtkWidget* oceancurrentYearEntry;
GtkWidget* oceancurrentNumberEntry;

// Ocean Conditions
GtkWidget* oceanconditionsCheckbox;
GtkWidget* oceanconditionsNumberEntry;

// Sailor Administration News
GtkWidget* sailorCheckbox;
GtkWidget* sailorNumberEntry;

// All Fishing Federations Newsletter
GtkWidget* fishingFederationsCheckbox;

// Sunday Newsletter
GtkWidget* sundayCheckbox;

// Sumo Match Update
GtkWidget* sumomatchCheckbox;

// Meta fields
GtkWidget* titleEntry;
GtkWidget* authorEntry;
GtkWidget* authorTitleEntry;
GtkWidget* receiversTextView;

// Number variables of the various faxes
int englishNumber = 0;
int japaneseNumber = 0;
int furusatoNumber = 0;
int kaiunsuisanNumber = 0;
int navreportFromNumber = 0;
int navreportToNumber = 0;
int oceancurrentYear = 0;
int oceancurrentNumber = 0;
int sailorNumber = 0;
int oceanconditionsNumber = 0;

std::string author = "";
std::string authorTitle = "";

// List of receiver checkboxes
std::vector<GtkWidget*> receiverCheckBoxes;

std::string title;

gboolean isNumeric(const gchar* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!g_ascii_isdigit(str[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

void processButtons() {
    title = "";

    gboolean kyodoChecked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(kyodoCheckbox));

    if (kyodoChecked) {
        title = gtk_button_get_label(GTK_BUTTON(kyodoCheckbox));

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(englishRadioButton))) {
            title += " ";
            title += gtk_button_get_label(GTK_BUTTON(englishRadioButton));
            title += " ";
            title += std::to_string(englishNumber);
        } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(japaneseRadioButton))) {
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(morningRadioButton))) {
                title += " ";
                title += gtk_button_get_label(GTK_BUTTON(morningRadioButton));
            } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(eveningRadioButton))) {
                title += " ";
                title += gtk_button_get_label(GTK_BUTTON(eveningRadioButton));
            }

            title += " ";
            title += gtk_button_get_label(GTK_BUTTON(japaneseRadioButton));
            title += " ";
            title += std::to_string(japaneseNumber);
        }

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sportsCheckbox))) {
            title += ", ";
            title += gtk_button_get_label(GTK_BUTTON(sportsCheckbox));
        }
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(furusatoCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(furusatoCheckbox));
        title += " ";
        title += std::to_string(furusatoNumber);
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(navreportCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(navreportCheckbox));
        title += " ";
        title += std::to_string(navreportFromNumber);

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(navreportToCheckbox))) {
            title += "-";
            title += std::to_string(navreportToNumber);
        }
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(kaiunsuisanCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(kaiunsuisanCheckbox));
        title += " ";
        title += std::to_string(kaiunsuisanNumber);
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(oceancurrentCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(oceancurrentCheckbox));
        title += " ";
        title += std::to_string(oceancurrentYear);
        title += "-";
        title += std::to_string(oceancurrentNumber);
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(oceanconditionsCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(oceanconditionsCheckbox));
        title += " ";
        title += std::to_string(oceanconditionsNumber);
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sailorCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(sailorCheckbox));
        title += " ";
        title += std::to_string(sailorNumber);
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fishingFederationsCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(fishingFederationsCheckbox));
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sundayCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(sundayCheckbox));
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sumomatchCheckbox))) {
        if (!title.empty()) {
            title += ", ";
        }

        title += gtk_button_get_label(GTK_BUTTON(sumomatchCheckbox));
    }

    g_print("%s\n", title.c_str());

    gtk_entry_set_text(GTK_ENTRY(titleEntry), title.c_str());
}

void onFaxEngJapCheckboxToggle(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
}

void onFaxMorningEveningCheckboxToggle(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(japaneseRadioButton), TRUE);
}

// Callback function for the "Kyodo News" checkbox
void onFaxCheckboxToggle(GtkWidget* widget, gpointer data) {
    processButtons();
}

void modalWindow(const gchar *message) {
    GtkWidget* dialog = gtk_message_dialog_new(
        GTK_WINDOW(window),            // Parent window
        GTK_DIALOG_MODAL,              // Dialog type (modal)
        GTK_MESSAGE_INFO,              // Message type (info)
        GTK_BUTTONS_OK,                // Buttons (OK)
        "%s",
        message
    );
    
    // Set dialog title
    gtk_window_set_title(GTK_WINDOW(dialog), "Message");
    
    // Run the dialog and wait for a response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    
    // Close the dialog
    gtk_widget_destroy(dialog);
}

void onSaveMetadataClicked(GtkWidget* widget, gpointer data) {
    const gchar* imagePath = gtk_entry_get_text(GTK_ENTRY(imagePathEntry));

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(imagePath);

    if (image.get() == nullptr) {
        modalWindow("Error: Failed to open the image!\n");
        return;
    }

    image->readMetadata();
    // Exiv2::XmpData& xmpData = image->xmpData(); // Decision is to rewrite the metadata, not to update it.
    Exiv2::XmpData xmpData;

    xmpData["Xmp.dc.title"] = gtk_entry_get_text(GTK_ENTRY(titleEntry));;
    xmpData["Xmp.dc.creator"] = author;
    xmpData["Xmp.photoshop.AuthorsPosition"] = authorTitle;

    GtkTextBuffer* buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(receiversTextView));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    xmpData["Xmp.dc.description"] = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);;

    image->setXmpData(xmpData);
    image->writeMetadata();

    modalWindow("Metadata saved to the image!");
}

void onNumberChanged(GtkEditable* editable, gpointer data, int* number) {
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(editable));

    // Validate the input as an integer
    if (isNumeric(text)) {
        *number = atoi(text); // Convert the valid text to an integer
    }

    processButtons();
}
// Callback function for the "+" button for English
void onEnglishIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(englishRadioButton), TRUE);
    gtk_entry_set_text(GTK_ENTRY(englishNumberEntry), (std::to_string(++englishNumber)).c_str());
}

void onEnglishNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(englishRadioButton), TRUE);
    onNumberChanged(editable, data, &englishNumber);
}

void onjapaneseIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(japaneseRadioButton), TRUE);
    gtk_entry_set_text(GTK_ENTRY(japaneseNumberEntry), (std::to_string(++japaneseNumber)).c_str());
}

void onJapaneseNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kyodoCheckbox), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(japaneseRadioButton), TRUE);
    onNumberChanged(editable, data, &japaneseNumber);
}

void onfurusatoIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(furusatoCheckbox), TRUE);
    gtk_entry_set_text(GTK_ENTRY(furusatoNumberEntry), (std::to_string(++furusatoNumber)).c_str());
}

void onFurusatoNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(furusatoCheckbox), TRUE);
    onNumberChanged(editable, data, &furusatoNumber);
}

void onNavreportMoveClicked(GtkWidget* widget, gpointer data) {
    navreportFromNumber = (++navreportToNumber);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(navreportCheckbox), TRUE);
    gtk_entry_set_text(GTK_ENTRY(navreportFromNumberEntry), (std::to_string(navreportFromNumber)).c_str());
    gtk_entry_set_text(GTK_ENTRY(navreportToNumberEntry), (std::to_string(navreportToNumber)).c_str());
}

void onNavreportFromNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(navreportCheckbox), TRUE);
    onNumberChanged(editable, data, &navreportFromNumber);
}

void onNavreportToNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(navreportCheckbox), TRUE);
    onNumberChanged(editable, data, &navreportToNumber);
}

void onKaiunsuisanIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kaiunsuisanCheckbox), TRUE);
    gtk_entry_set_text(GTK_ENTRY(kaiunsuisanNumberEntry), (std::to_string(++kaiunsuisanNumber)).c_str());
}

void onKaiunsuisanNumberChanged(GtkEditable* editable, gpointer data) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(kaiunsuisanCheckbox), TRUE);
    onNumberChanged(editable, data, &kaiunsuisanNumber);
}

void onOceancurrentYearIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(oceancurrentYearEntry), (std::to_string(++oceancurrentYear)).c_str());
}

void onOceancurrentYearChanged(GtkEditable* editable, gpointer data) {
    onNumberChanged(editable, data, &oceancurrentYear);
}

void onOceancurrentNumberIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(oceancurrentNumberEntry), (std::to_string(++oceancurrentNumber)).c_str());
}

void onOceancurrentNumberChanged(GtkEditable* editable, gpointer data) {
    onNumberChanged(editable, data, &oceancurrentNumber);
}

void onOceanconditionsNumberIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(oceanconditionsNumberEntry), (std::to_string(++oceanconditionsNumber)).c_str());
}

void onOceanconditionsNumberChanged(GtkEditable* editable, gpointer data) {
    onNumberChanged(editable, data, &oceanconditionsNumber);
}

void onSailorNumberIncrementClicked(GtkWidget* widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(sailorNumberEntry), (std::to_string(++sailorNumber)).c_str());
}

void onSailorNumberChanged(GtkEditable* editable, gpointer data) {
    onNumberChanged(editable, data, &sailorNumber);
}

void onAuthorChanged(GtkEditable* editable, gpointer data) {
    author = gtk_entry_get_text(GTK_ENTRY(editable));
}

void onAuthorTitleChanged(GtkEditable* editable, gpointer data) {
    authorTitle = gtk_entry_get_text(GTK_ENTRY(editable));
}

void onReceiverCheckboxToggled(GtkWidget* widget, gpointer data) {
    std::string checkedReceivers = "";

    for (auto & receiverCheckbox : receiverCheckBoxes) {
        gboolean receiverChecked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(receiverCheckbox));
        const gchar* label = gtk_button_get_label(GTK_BUTTON(receiverCheckbox));

        if (receiverChecked) {
            if (!checkedReceivers.empty()) {
                checkedReceivers += "\n";
            }

            checkedReceivers += label;
        }
    }

    GtkTextBuffer* buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(receiversTextView));
    gtk_text_buffer_set_text(buffer, checkedReceivers.c_str(), -1);
}

// Callback function for the "Browse" button
void onBrowse(GtkWidget* widget, gpointer data) {
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "PNG Files");
    gtk_file_filter_add_pattern(filter, "*.png");

    GtkWidget* fileChooser = gtk_file_chooser_dialog_new("Open Image", GTK_WINDOW(data), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fileChooser), filter);

    if (gtk_dialog_run(GTK_DIALOG(fileChooser)) == GTK_RESPONSE_ACCEPT) {
        char* filePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileChooser));
        gtk_entry_set_text(GTK_ENTRY(imagePathEntry), filePath);
        g_free(filePath);
    }

    gtk_widget_destroy(fileChooser);
}

void loadFromJson() {
    Json::Value jsonData;
    std::ifstream file("kyodo-meta.json");
    if (file.is_open()) {
        file >> jsonData;
        file.close();

        if (jsonData.isMember("kyodo_english") && jsonData["kyodo_english"].isInt()) {
            englishNumber = jsonData["kyodo_english"].asInt();
        }

        if (jsonData.isMember("kyodo_japanese") && jsonData["kyodo_japanese"].isInt()) {
            japaneseNumber = jsonData["kyodo_japanese"].asInt();
        }

        if (jsonData.isMember("furusato") && jsonData["furusato"].isInt()) {
            furusatoNumber = jsonData["furusato"].asInt();
        }

        if (jsonData.isMember("kaiun_suisan") && jsonData["kaiun_suisan"].isInt()) {
            kaiunsuisanNumber = jsonData["kaiun_suisan"].asInt();
        }

        if (jsonData.isMember("sailor_news") && jsonData["sailor_news"].isInt()) {
            sailorNumber = jsonData["sailor_news"].asInt();
        }

        if (jsonData.isMember("ocean_conditions") && jsonData["ocean_conditions"].isInt()) {
            oceanconditionsNumber = jsonData["ocean_conditions"].asInt();
        }

        if (jsonData.isMember("nav_report")) {
            if (jsonData["nav_report"].isMember("from") && jsonData["nav_report"]["from"].isInt()) {
                navreportFromNumber = jsonData["nav_report"]["from"].asInt();
            }
            if (jsonData["nav_report"].isMember("to") && jsonData["nav_report"]["to"].isInt()) {
                navreportToNumber = jsonData["nav_report"]["to"].asInt();
            }
        }

        if (jsonData.isMember("ocean_current")) {
            if (jsonData["ocean_current"].isMember("year") && jsonData["ocean_current"]["year"].isInt()) {
                oceancurrentYear = jsonData["ocean_current"]["year"].asInt();
            }
            if (jsonData["ocean_current"].isMember("number") && jsonData["ocean_current"]["number"].isInt()) {
                oceancurrentNumber = jsonData["ocean_current"]["number"].asInt();
            }
        }

        if (jsonData.isMember("author")) {
            author = jsonData["author"].asString();
        }

        if (jsonData.isMember("author_title")) {
            authorTitle = jsonData["author_title"].asString();
        }

        // Extract the list of receivers
        if (jsonData.isMember("receivers") && jsonData["receivers"].isArray()) {
            for (const Json::Value& receiver : jsonData["receivers"]) {
                if (receiver.isString()) {
        //             receivers.push_back(receiver.asString());
                    GtkWidget *receiverCheckbox =  gtk_check_button_new_with_label(receiver.asString().c_str());
                    receiverCheckBoxes.push_back(receiverCheckbox);
                    g_signal_connect(receiverCheckbox, "toggled", G_CALLBACK(onReceiverCheckboxToggled), (gpointer)receiver.asString().c_str());
                }
            }
        }
    } else {
        g_print("Error: Failed to load the JSON file.\n");
    }
}

void saveToJson() {
    Json::Value jsonData;
    std::ifstream file("kyodo-meta.json");
    
    if (file.is_open()) {
        file >> jsonData;
        file.close();
    } else {
        g_print("Error: Failed to load the JSON file before saving.\n");
    }

    jsonData["kyodo_english"] = englishNumber;
    jsonData["kyodo_japanese"] = japaneseNumber;
    jsonData["furusato"] = furusatoNumber;
    jsonData["kaiun_suisan"] = kaiunsuisanNumber;
    jsonData["sailor_news"] = sailorNumber;
    jsonData["ocean_conditions"] = oceanconditionsNumber;

    Json::Value navreportData;
    navreportData["from"] = navreportFromNumber;
    navreportData["to"] = navreportToNumber;
    jsonData["nav_report"] = navreportData;

    Json::Value oceancurrentData;
    oceancurrentData["year"] = oceancurrentYear;
    oceancurrentData["number"] = oceancurrentNumber;
    jsonData["ocean_current"] = oceancurrentData;

    jsonData["author"] = author;
    jsonData["author_title"] = authorTitle;

    std::ofstream outFile("kyodo-meta.json");
    
    if (outFile.is_open()) {
        outFile << jsonData;
        outFile.close();
    } else {
        g_print("Error: Failed to save metadata to JSON file.\n");
    }
}

int main(int argc, char* argv[]) {
    GtkWidget* vbox;
    GtkWidget* browseButton;
    GtkWidget* grid;

    gtk_init(&argc, &argv);

    loadFromJson();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kyodo News Metadata Editor");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GdkPixbuf* icon = gdk_pixbuf_new_from_xpm_data(icon_png);
    
    if (icon != NULL) {
        // Set the application icon for the main window
        gtk_window_set_icon(GTK_WINDOW(window), icon);
        g_object_unref(icon); // Release the icon when done
    } else {
        g_warning("Failed to create GdkPixbuf from embedded icon data.");
    }
    // gtk_window_set_icon_from_file(GTK_WINDOW(window), "icon.png", NULL);


    // vbox = gtk_vbox_new(FALSE, 10);
    vbox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a grid to organize elements in rows and columns
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(vbox), grid);

    // Row 1: Image Input Field and Browse Button
    imagePathEntry = gtk_entry_new();
    browseButton = gtk_button_new_with_label("Browse");
    g_signal_connect(browseButton, "clicked", G_CALLBACK(onBrowse), window);

    int row = 0;
    gtk_grid_attach(GTK_GRID(grid), imagePathEntry, 0, row, 6, 1);
    gtk_grid_attach(GTK_GRID(grid), browseButton, 6, row++, 1, 1);

    // Row 2: Kyodo News Checkbox
    kyodoCheckbox = gtk_check_button_new_with_label("Kyodo News");
    g_signal_connect(kyodoCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), kyodoCheckbox, 0, row++, 2, 1);

    // Row 3: Radio Buttons, Labels, Numeric Entry Fields, and "+" Button for English
    englishRadioButton = gtk_radio_button_new_with_label(NULL, "English");
    g_signal_connect(englishRadioButton, "clicked", G_CALLBACK(onFaxEngJapCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), englishRadioButton, 0, row, 1, 1);

    englishNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(englishNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(englishNumberEntry), (std::to_string(englishNumber)).c_str());
    g_signal_connect(englishNumberEntry, "changed", G_CALLBACK(onEnglishNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), englishNumberEntry, 1, row, 1, 1);

    GtkWidget* englishIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(englishIncrementButton, "clicked", G_CALLBACK(onEnglishIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), englishIncrementButton, 2, row++, 1, 1);
    
    japaneseRadioButton = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(englishRadioButton), "Japanese");
    // No need to attach signal, as the second radio button is attached to the first one!
    // g_signal_connect(japaneseRadioButton, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), japaneseRadioButton, 0, row, 1, 1);

    japaneseNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(japaneseNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(japaneseNumberEntry), (std::to_string(japaneseNumber)).c_str());
    g_signal_connect(japaneseNumberEntry, "changed", G_CALLBACK(onJapaneseNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), japaneseNumberEntry, 1, row, 1, 1);

    GtkWidget* japaneseIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(japaneseIncrementButton, "clicked", G_CALLBACK(onjapaneseIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), japaneseIncrementButton, 2, row++, 1, 1);

    morningRadioButton = gtk_radio_button_new_with_label(NULL, "Morning");
    g_signal_connect(morningRadioButton, "clicked", G_CALLBACK(onFaxMorningEveningCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), morningRadioButton, 1, row++, 1, 1);

    eveningRadioButton = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(morningRadioButton), "Evening");
    // g_signal_connect(eveningRadioButton, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), eveningRadioButton, 1, row++, 1, 1);

    sportsCheckbox = gtk_check_button_new_with_label("Sports");
    g_signal_connect(sportsCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), sportsCheckbox, 0, row++, 2, 1);

    // Furusato
    furusatoCheckbox = gtk_check_button_new_with_label("Kyodo Furusato News");
    g_signal_connect(furusatoCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), furusatoCheckbox, 0, row, 1, 1);

    furusatoNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(furusatoNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(furusatoNumberEntry), (std::to_string(furusatoNumber)).c_str());
    g_signal_connect(furusatoNumberEntry, "changed", G_CALLBACK(onFurusatoNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), furusatoNumberEntry, 1, row, 1, 1);
    
    GtkWidget* furusatoIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(furusatoIncrementButton, "clicked", G_CALLBACK(onfurusatoIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), furusatoIncrementButton, 2, row++, 1, 1);

    // Navigation Report
    navreportCheckbox = gtk_check_button_new_with_label("Navigation Report");
    g_signal_connect(navreportCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), navreportCheckbox, 0, row, 1, 1);

    navreportFromNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(navreportFromNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(navreportFromNumberEntry), (std::to_string(navreportFromNumber)).c_str());
    g_signal_connect(navreportFromNumberEntry, "changed", G_CALLBACK(onNavreportFromNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), navreportFromNumberEntry, 1, row, 1, 1);

    GtkWidget* navreportMoveButton = gtk_button_new_with_label("<");
    g_signal_connect(navreportMoveButton, "clicked", G_CALLBACK(onNavreportMoveClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), navreportMoveButton, 2, row, 1, 1);

    navreportToNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(navreportToNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(navreportToNumberEntry), (std::to_string(navreportToNumber)).c_str());
    g_signal_connect(navreportToNumberEntry, "changed", G_CALLBACK(onNavreportToNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), navreportToNumberEntry, 3, row, 1, 1);

    navreportToCheckbox = gtk_check_button_new();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(navreportToCheckbox), TRUE);
    g_signal_connect(navreportToCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), navreportToCheckbox, 4, row++, 1, 1);

    // Kaiun-Suisan
    kaiunsuisanCheckbox = gtk_check_button_new_with_label("Kaiun-Suisan News");
    g_signal_connect(kaiunsuisanCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), kaiunsuisanCheckbox, 0, row, 1, 1);

    kaiunsuisanNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(kaiunsuisanNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(kaiunsuisanNumberEntry), (std::to_string(kaiunsuisanNumber)).c_str());
    g_signal_connect(kaiunsuisanNumberEntry, "changed", G_CALLBACK(onKaiunsuisanNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), kaiunsuisanNumberEntry, 1, row, 1, 1);
    
    GtkWidget* kaiunsuisanIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(kaiunsuisanIncrementButton, "clicked", G_CALLBACK(onKaiunsuisanIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), kaiunsuisanIncrementButton, 2, row++, 1, 1);

    // Ocean Current Forecastings
    oceancurrentCheckbox = gtk_check_button_new_with_label("Ocean Current Forecastings");
    g_signal_connect(oceancurrentCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceancurrentCheckbox, 0, row, 1, 1);

    oceancurrentYearEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(oceancurrentYearEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(oceancurrentYearEntry), (std::to_string(oceancurrentYear)).c_str());
    g_signal_connect(oceancurrentYearEntry, "changed", G_CALLBACK(onOceancurrentYearChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceancurrentYearEntry, 1, row, 1, 1);

    GtkWidget* oceancurrentYearIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(oceancurrentYearIncrementButton, "clicked", G_CALLBACK(onOceancurrentYearIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceancurrentYearIncrementButton, 2, row, 1, 1);

    oceancurrentNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(oceancurrentNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(oceancurrentNumberEntry), (std::to_string(oceancurrentNumber)).c_str());
    g_signal_connect(oceancurrentNumberEntry, "changed", G_CALLBACK(onOceancurrentNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceancurrentNumberEntry, 3, row, 1, 1);

    GtkWidget* oceancurrentNumberIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(oceancurrentNumberIncrementButton, "clicked", G_CALLBACK(onOceancurrentNumberIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceancurrentNumberIncrementButton, 4, row++, 1, 1);

    // Ocean Conditions
    oceanconditionsCheckbox = gtk_check_button_new_with_label("Ocean Conditions");
    g_signal_connect(oceanconditionsCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceanconditionsCheckbox, 0, row, 1, 1);

    oceanconditionsNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(oceanconditionsNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(oceanconditionsNumberEntry), (std::to_string(oceanconditionsNumber)).c_str());
    g_signal_connect(oceanconditionsNumberEntry, "changed", G_CALLBACK(onOceanconditionsNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceanconditionsNumberEntry, 1, row, 1, 1);

    GtkWidget* oceanconditionsNumberIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(oceanconditionsNumberIncrementButton, "clicked", G_CALLBACK(onOceanconditionsNumberIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), oceanconditionsNumberIncrementButton, 2, row++, 1, 1);

    // Sailor Administration News
    sailorCheckbox = gtk_check_button_new_with_label("Sailor Administration News");
    g_signal_connect(sailorCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), sailorCheckbox, 0, row, 1, 1);

    sailorNumberEntry = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(sailorNumberEntry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_text(GTK_ENTRY(sailorNumberEntry), (std::to_string(sailorNumber)).c_str());
    g_signal_connect(sailorNumberEntry, "changed", G_CALLBACK(onSailorNumberChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), sailorNumberEntry, 1, row, 1, 1);

    GtkWidget* sailorNumberIncrementButton = gtk_button_new_with_label("+");
    g_signal_connect(sailorNumberIncrementButton, "clicked", G_CALLBACK(onSailorNumberIncrementClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), sailorNumberIncrementButton, 2, row++, 1, 1);

    // All Fishing Federations Newsletter
    fishingFederationsCheckbox = gtk_check_button_new_with_label("All Fishing Federations Newsletter");
    g_signal_connect(fishingFederationsCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), fishingFederationsCheckbox, 0, row++, 1, 1);

    // Sunday Newsletter
    sundayCheckbox = gtk_check_button_new_with_label("Sunday Newsletter");
    g_signal_connect(sundayCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), sundayCheckbox, 0, row++, 1, 1);

    // Sumo Match Update
    sumomatchCheckbox = gtk_check_button_new_with_label("Sumo Match Update");
    g_signal_connect(sumomatchCheckbox, "toggled", G_CALLBACK(onFaxCheckboxToggle), NULL);
    gtk_grid_attach(GTK_GRID(grid), sumomatchCheckbox, 0, row++, 1, 1);

    // XMP Metadata Fields
    GtkWidget *titleSpacer = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), titleSpacer, 0, row++, 1, 1);

    GtkWidget* titleLabel = gtk_label_new("Document Title:");
    gtk_label_set_xalign (GTK_LABEL(titleLabel), 0.0);
    gtk_grid_attach(GTK_GRID(grid), titleLabel, 0, row++, 1, 1);

    titleEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), titleEntry, 0, row++, 5, 1);

    GtkWidget* authorLabel = gtk_label_new("Author:");
    gtk_label_set_xalign (GTK_LABEL(authorLabel), 0.0);
    gtk_grid_attach(GTK_GRID(grid), authorLabel, 0, row, 1, 1);

    authorEntry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(authorEntry), author.c_str());
    g_signal_connect(authorEntry, "changed", G_CALLBACK(onAuthorChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), authorEntry, 1, row++, 4, 1);

    GtkWidget* authorTitleLabel = gtk_label_new("Author Title:");
    gtk_label_set_xalign (GTK_LABEL(authorTitleLabel), 0.0);
    gtk_grid_attach(GTK_GRID(grid), authorTitleLabel, 0, row, 1, 1);

    authorTitleEntry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(authorTitleEntry), authorTitle.c_str());
    g_signal_connect(authorTitleEntry, "changed", G_CALLBACK(onAuthorTitleChanged), NULL);
    gtk_grid_attach(GTK_GRID(grid), authorTitleEntry, 1, row++, 4, 1);

    GtkWidget* receiversLabel = gtk_label_new("Description (List of Receivers):");
    gtk_label_set_xalign (GTK_LABEL(receiversLabel), 0.0);
    gtk_grid_attach(GTK_GRID(grid), receiversLabel, 0, row++, 1, 1);

    for (int i = 0; i < 4; i++) {
        GtkWidget* scrollSpacerLabel = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(grid), scrollSpacerLabel, 0, row++, 1, 1);
    }

    GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_grid_attach(GTK_GRID(grid), scrolledWindow, 0, row-4, 5, 4);

    gtk_widget_set_hexpand(scrolledWindow, TRUE);
    gtk_widget_set_vexpand(scrolledWindow, TRUE);

    receiversTextView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolledWindow), receiversTextView);
    
    GtkWidget* saveMetadataButton = gtk_button_new_with_label("Save Metadata");
    g_signal_connect(saveMetadataButton, "clicked", G_CALLBACK(onSaveMetadataClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), saveMetadataButton, 0, row, 5, 1);


    // Receivers
    int rrow = 1;

    GtkWidget* receiverListSpacerLabel = gtk_label_new("    ");
    gtk_grid_attach(GTK_GRID(grid), receiverListSpacerLabel, 5, rrow, 1, 1);

    GtkWidget* receiverListLabel = gtk_label_new("Receivers:");
    gtk_label_set_xalign (GTK_LABEL(receiverListLabel), 0.0);
    gtk_grid_attach(GTK_GRID(grid), receiverListLabel, 6, rrow++, 1, 1);

    for (auto & receiverCheckbox : receiverCheckBoxes) {
        gtk_grid_attach(GTK_GRID(grid), receiverCheckbox, 6, rrow++, 1, 1);
    }

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();

    saveToJson();

    g_print("Exiting...\n");

    return 0;
}
