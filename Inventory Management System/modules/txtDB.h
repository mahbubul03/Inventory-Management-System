#ifndef TEXTFILE_H
#define TEXTFILE_H
using namespace std;




class txtDB
{
private:
    string gurbage;
    char *txt_file_name;
    char *splitter_pattern;
public:
    txtDB(char *DBfilename,char *split_pattern);
    int countRecord(); // counts the number of row/records of data
    int countField(); // counts the number of fields
    int eraseALL();
    int addRecord(int record_index,const char *record);// add a new record to specific index
    int removeRecord(int record_index);
    string getData(int field_index,int record_index);//get data by grid address of the table
    vector<string> searchRecord(int field_index, const string &field_value); // search records by field value
    vector<pair<string, int>> searchRecords(int field_index, const string &field_value);
    vector<string> getAllRecords();

};






txtDB::txtDB(char *DBfilename,char *split_pattern)
{
    txt_file_name=DBfilename;
    splitter_pattern=split_pattern;
}
int txtDB::countRecord()
{
    int counter = 0;
    ifstream file(txt_file_name);
    if (!file.is_open())return -1; //can't open file Return an error code
    while (getline(file, gurbage))
    {
        ++counter;
    }
    file.close();
    return counter;
}



int txtDB::countField()
{
    int counter = 0;
    ifstream file(txt_file_name);
    if (!file.is_open())return -1; //can't open file Return an error code
    while (getline(file, gurbage))
    {
        char *token = strtok(const_cast<char *>(gurbage.c_str()), splitter_pattern);
        while (token != nullptr)
        {
            ++counter;
            token = strtok(nullptr, splitter_pattern);
        }
        break; // Count fields in only the first line for simplicity
    }
    file.close();
    return counter;
}


// Erases all contents of the text file
int txtDB::eraseALL()
{
    ofstream file(txt_file_name);
    if (!file.is_open()) return -1; // Error: can't open file, return an error code
    file.close();
    return 0; // Success: file contents erased
}

// Adds a new record to a specific index in the text file
int txtDB::addRecord(int record_index,const char *record)
{
    // Read all existing records
    ifstream infile(txt_file_name);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return 0;
    }

    vector<string> records;
    string line;
    while (getline(infile, line))
    {
        records.push_back(line);
    }
    infile.close();

    // Check if the index is valid
    if (record_index < 0 || record_index > records.size())
    {
        cerr << "Error: Invalid record index." << endl;
        return 0;
    }

    // Insert the new record at the specified index
    records.insert(records.begin() + record_index, record);

    // Write all records back to the file
    ofstream outfile(txt_file_name);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return 0;
    }

    for (const auto &r : records)
    {
        outfile << r << endl;
    }
    outfile.close();

    return 1; // Success
}




// Get data by grid address of the table
string txtDB::getData(int field_index, int record_index)
{
    ifstream infile(txt_file_name);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return "";
    }

    string line;
    int counter=0;
    int current_record_index = 0;
    while (getline(infile, line))
    {
        if (current_record_index == record_index)
        {
            istringstream iss(line);
            string field;
            int current_field_index = 0;

            char *token = strtok(const_cast<char *>(line.c_str()), splitter_pattern);
            while (token != nullptr)
            {
                ++counter;
                token = strtok(nullptr, splitter_pattern);
                if(counter==field_index)return token;
            }



            while (getline(iss, field, *splitter_pattern))   // Use the splitter pattern to tokenize fields
            {
                if (current_field_index == field_index)
                {
                    infile.close();
                    return field;
                }
                ++current_field_index;
            }
        }
        ++current_record_index;
    }

    infile.close();
    cerr << "Error: Grid address out of bounds." << endl;
    return "";
}

int txtDB::removeRecord(int record_index)
{
    // Read all existing records
    ifstream infile(txt_file_name);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return -1;
    }

    vector<string> records;
    string line;
    while (getline(infile, line))
    {
        records.push_back(line);
    }
    infile.close();

    // Check if the index is valid
    if (record_index < 0 || record_index >= records.size())
    {
        cerr << "Error: Invalid record index." << endl;
        return -1;
    }

    // Remove the record at the specified index
    records.erase(records.begin() + record_index);

    // Write all records back to the file
    ofstream outfile(txt_file_name);
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return -1;
    }

    for (const auto &r : records)
    {
        outfile << r << endl;
    }
    outfile.close();

    return 0; // Success
}


vector<string> txtDB::searchRecord(int field_index, const string &field_value)
{
    vector<string> matching_records;

    ifstream infile(txt_file_name);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        matching_records.push_back("No Record Found");
        return matching_records;
    }

    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string field;
        int current_field_index = 0;

        char *token = strtok(const_cast<char *>(line.c_str()), splitter_pattern);
        while (token != nullptr)
        {
            if (current_field_index == field_index && string(token) == field_value)
            {
                matching_records.push_back(line);
                break;
            }
            ++current_field_index;
            token = strtok(nullptr, splitter_pattern);
        }
    }

    infile.close();
    return matching_records;
}


vector<pair<string, int>> txtDB::searchRecords(int field_index, const string &field_value) {
    vector<pair<string, int>> matching_records;

    ifstream infile(txt_file_name);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return matching_records;
    }

    string line;
    int line_index = 0;
    while (getline(infile, line)) {
        istringstream iss(line);
        string field;
        int current_field_index = 0;

        char *token = strtok(const_cast<char *>(line.c_str()), splitter_pattern);
        while (token != nullptr) {
            if (current_field_index == field_index && string(token) == field_value) {
                matching_records.push_back(make_pair(line, line_index));
                break;
            }
            ++current_field_index;
            token = strtok(nullptr, splitter_pattern);
        }
        ++line_index;
    }

    infile.close();
    return matching_records;
}

// Get all records
vector<string> txtDB::getAllRecords()
{
    vector<string> records;
    ifstream infile(txt_file_name);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return records;
    }
    string line;
    while (getline(infile, line))
    {
        records.push_back(line);
    }

    infile.close();
    return records;
}




#endif
