#include <vector>
#include <string>
#include <iostream>

using namespace std;

class multiplTree {
private:
    string name;
    string value;
    vector<multiplTree*> children;

public:
    multiplTree(const string& name = "", const string& value = "") : name(name), value(value) {}

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return this->name;
    }

    void setValue(const string& value) {
        this->value = value;
    }

    void setValue(double value) {
        this->value = to_string(value);
    }

    void setValue(int value) {
        this->value = to_string(value);
    }

    string getValue() const {
        return this->value;
    }

    bool isInt() const {
        char* p;
        strtol(this->value.c_str(), &p, 10);
        return *p == 0;
    }

    bool isDouble() const {
        char* p;
        strtod(this->value.c_str(), &p);
        return *p == 0;
    }

    int getInt() const {
        if (isInt()) {
            return stoi(this->value);
        }
        return 0;
    }

    double getDouble() const {
        if (isDouble()) {
            return stod(this->value);
        }
        return 0.0;
    }

    size_t getCountSub() const {
        return this->children.size();
    }

    multiplTree* getSub(size_t i) {
        if (i < this->children.size()) {
            return this->children[i];
        }
        return nullptr;
    }

    multiplTree* getSub(const string& name) {
        for (auto& child : this->children) {
            if (child->getName() == name) {
                return child;
            }
        }
        return nullptr;
    }

    void addSub(multiplTree* node) {
        this->children.push_back(node);
    }

    multiplTree* findNode(const string& name) {
        if (this->name == name) {
            return this;
        }
        for (auto& child : this->children) {
            multiplTree* found = child->findNode(name);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    // Загрузка из XML
    void loadFromXML(const string& xml) {
        size_t pos = 0;
        while ((pos = xml.find("<", pos)) != string::npos) {
            size_t endPos = xml.find(">", pos);
            if (endPos == string::npos) break;

            string element = xml.substr(pos + 1, endPos - pos - 1);
            size_t valuePos = xml.find("</" + element + ">", endPos);
            if (valuePos == string::npos) break;

            string value = xml.substr(endPos + 1, valuePos - endPos - 1);
            multiplTree* node = new multiplTree(element, value);
            addSub(node);

            pos = valuePos + element.size() + 3;
        }
    }

    // Выдача в удобном для обработке порядке
    void print(int level = 0) const {
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << getName() << ": " << getValue() << endl;

        for (auto& child : children) {
            child->print(level + 1);
        }
    }
    
};



int main() {
    // Создание экземпляра класса multiplTree
    multiplTree tree;

    // Загрузка данных из XML
    string xml = "<root>rootValue<child1>value1</child1><child2>value2</child2></root>";
    tree.loadFromXML(xml);

    // Вывод дерева в удобном для обработки порядке
    tree.print();

    return 0;
}

