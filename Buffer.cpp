// Buffer.cpp

#include "Buffer.h"

using namespace std;

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
		if (i < v_lines_.size())
			cout << std::setw(6) << i+1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file)
        return false;

    v_lines_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.

    string line;
    while (getline(file, line)){
		anchor(line);
        v_lines_.push_back(line);
	}
    file_name_ = new_file_name;
    ix_top_line_ = 0;
    return true;
}

bool Buffer::move_to_search(const string & target)
{
    for (int i = ix_top_line_; i < v_lines_.size(); ++i){
        if(v_lines_[i].find(target) != string::npos){
            ix_top_line_ = i;
            return true;
        }
    }
	return false;
}

void Buffer::anchor(string & line)
{
	string link;
	string info;
	size_t start_anchor = line.find("<a");
	if (start_anchor != string::npos){
		size_t end_anchor = line.find(">", start_anchor);
		if(end_anchor != string::npos){
			istringstream anchor(line.substr(start_anchor + 2, end_anchor - start_anchor - 2));
			anchor >> link >> info;
			anchor >> ws;
			if(anchor.eof()){
				v_links_.push_back(link);
				line.replace(start_anchor + 1, end_anchor - start_anchor, info + ">" + "[" + to_string(v_links_.size()) + "]");
			}
		}
	}
}
