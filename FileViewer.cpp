// FileViewer.cpp

#include "FileViewer.h"

using namespace std;

void FileViewer::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    system("clear");

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  search  go open  quit\n";
    cout << short_separator << endl;
}

void FileViewer::execute_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            buffer_.move_to_next_page();
            break;
        }

        case 'o': {
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);
            if (!buffer_.open(file_name))
                error_message_ = "Could not open " + file_name;
            break;
        }
	
		case 's' : {
			cout << "desired string: ";
			string search_target;
			getline(cin, search_target);
			if (!buffer_.move_to_search(search_target))
				error_message_ = "String \"" + search_target + "\" was not found";
			break;
		}

        case 'p': {
            buffer_.move_to_previous_page();
            break;
        }

		case 'g': {

			break;
		}
        case 'q': {
            done = true;
            break;
        }
    }
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);

    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}


