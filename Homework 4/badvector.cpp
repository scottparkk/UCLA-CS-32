void removeBad(vector<Restaurant*>& v)
{
	for (vector<Restaurant*> ::iterator i = v.begin(); i != v.end();) {
		if ((*i)->stars() <= 2) {
			delete* i;
			i = v.erase(i);
		}
		else
			i++;
	}
}
