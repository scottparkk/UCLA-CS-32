
void listAll(const Domain* d, string path) // two-parameter overload
{  
    if (path != d->label() && path!= "")
        path = d->label() + "." + path;
    else
        path = d->label();
    if (d->subdomains().empty()) {
        cout << path << endl;
    }
    for (int i = 0; i < d->subdomains().size(); i++) {
        listAll(d->subdomains()[i], path);
    }
}