#include <string>
#include "tool.h"
using namespace std;

int check(string st, int MIN, int MAX)
{
	int i, s = 0, l = st.size();
	if ((st[0] == '+') || (st[0] == '-'))
		s++;
	for (i = s; i < l; i++)
		if ((st[i] < '0') || (st[i] > '9'))
			return -1;
	s = atoi(st.c_str());
	if ((s < MIN) || (s > MAX))
		return -1;
	else
		return 0;
}
