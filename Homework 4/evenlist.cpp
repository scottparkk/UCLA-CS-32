void removeEven(list<int>& li)
{
	for (list<int> ::iterator i = li.begin(); i != li.end();) {
		if (*i % 2 == 0)
			i = li.erase(i);
		else
			i++;
	}
}
