
class Landmark {
public:
    Landmark(string name): lname(name) {}
    string name() const {
        return lname;
    }

    virtual string color() const {
        return "yellow";
    }
    virtual string icon() const = 0;
    virtual ~Landmark()=0{}
private:
   string lname;
};

class Hotel : public Landmark {
public:
    Hotel(string name) : Landmark(name){}
    virtual string icon() const {
        return "bed";
    }
    virtual ~Hotel() {
        cout << "Destroying the hotel " << Landmark::name() << "."<<endl;
    }
private:

};

class Restaurant : public Landmark {
public:
    Restaurant(string name, int capacity): Landmark(name), m_capacity(capacity) {}
    virtual string icon() const {
        string first = "";
        if (m_capacity >= 40)
            first = "large ";
        else
            first = "small ";
        return first + "knife/fork";
    }
    virtual ~Restaurant() {
        cout << "Destroying the restaurant " << Landmark::name() << "." << endl;
    }
private:
    int m_capacity;
};

class Hospital : public Landmark {
public:
    Hospital(string name) : Landmark(name) {}
    virtual string color() const {
        return "blue";
    }
    virtual string icon() const {
        return "H";
    }
    virtual ~Hospital() {
        cout << "Destroying the hospital " << Landmark::name() << "." << endl;
    }
};
