    #include <iostream>
    #include <fstream>
    #include <list>
    #include <string>
    #include <vector>
    #include <sstream>
    #define TABLE_SIZE 2000
    using namespace std;

    struct Company{
        string name;
        string profit_tax;
        string address;
    };

    struct Hashtable{
        list<Company> table[TABLE_SIZE];
    };

    vector<Company> readcompany(const string& infile){
        vector<Company> companies;
        ifstream inputfile(infile);
        if(!inputfile){
            cerr << "Khong the doc file"<<endl;
            return companies;
        }
        string line;
        getline(inputfile,line);

        while (getline(inputfile, line)) {
        string name, profit_tax, address;
        stringstream ss(line);
        if (getline(ss, name, '|') && 
                getline(ss, profit_tax, '|') && 
                getline(ss, address)) {
                Company c = {name, profit_tax, address};
                companies.push_back(c);
            } else {
                cerr << "Dong khong hop le: " << line << endl;
            }
        }
        inputfile.close();
        return companies;
    }

    long long hashString(string s ){
        long long hash = 0; 
        const long long m = 1e9 + 9;
        for(char c : s ){
            hash = (hash*31 + c ) %  m;
        }
        return hash;
    }

    Hashtable* createhashtable(vector<Company> list_company){
        Hashtable* hash_table =new Hashtable();
        for (const auto& Company : list_company) {
            long long hash_value = hashString(Company.name) % TABLE_SIZE;
            hash_table->table[hash_value].push_back(Company);
        }
        return hash_table;
    }

   void insert(Hashtable* hash_table, Company company) {
    long long hash_value = hashString(company.name) % TABLE_SIZE;
    for (auto& c : hash_table->table[hash_value]) {
        if (c.name == company.name) {
            return; 
        }
    }
    hash_table->table[hash_value].push_back(company);
}

    Company* search(Hashtable* hash_table, string company_name) {
        long long hash_value = hashString(company_name) % TABLE_SIZE;
        for (auto& Company : hash_table->table[hash_value]) {
            if (Company.name == company_name) {
                return &Company;
            }
        }   
        return nullptr;
    }

    void deleteHashTable(Hashtable* hash_table) {
    if (hash_table) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            hash_table->table[i].clear();
        }
        delete hash_table;
    }
}

    int main(int argc, char* argv[]) {
        if (argc != 4) {
            cerr << "Su dung: ./main <MST.txt> <input.txt> <output.txt>" << endl;
            return 1;
        }

        string mst_file = argv[1];
        string input_file = argv[2];
        string output_file = argv[3];


        vector<Company> companies = readcompany(mst_file);
        if (companies.empty()) {
            cerr << "Khong doc duoc danh sach cong ty" << endl;
            return 1;
        }


        Hashtable* hash_table = createhashtable(companies);


        ifstream input(input_file);
        ofstream output(output_file);
        if (!input || !output) {
            cerr << "Khong the mo file input/output" << endl;
            delete hash_table;
            return 1;
        }

        string company_name;
        while (getline(input, company_name)) {
            Company* result = search(hash_table, company_name);
            if (result) {
                output << result->name << "|" << result->profit_tax << "|" << result->address << endl;
            } else {
                output << company_name << "|NOT_FOUND" << endl;
            }
        }

        input.close();
        output.close();

        delete hash_table; 

        return 0;
    }