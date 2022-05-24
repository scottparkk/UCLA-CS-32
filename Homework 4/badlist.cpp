void removeBad(list<Restaurant*>& li)
{
	for (list<Restaurant*> ::iterator i = li.begin(); i != li.end();) {
		if ((*i)->stars() <= 2) {
			delete* i;
			i = li.erase(i);
		}
		else
			i++;
	}
}
