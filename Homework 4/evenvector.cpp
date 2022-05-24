void removeEven(vector<int>& v)
{
	for (vector<int> ::iterator i = v.begin(); i != v.end();) {
		if (*i % 2 == 0)
			i = v.erase(i);
		else
			i++;
	}
}