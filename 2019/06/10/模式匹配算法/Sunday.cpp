#include <cstdio>
#include <string>

using String = std::string;

int SundaySearch(const String& strText, const String& strSubText)
{
	int nTextLen = strText.length();
	int nSubTextLen = strSubText.length();
	if (nTextLen == 0 || nSubTextLen == 0 || nTextLen < nSubTextLen)
	{
		return -1;
	}
	for (int i = 0; i <= nTextLen - nSubTextLen; i++)
	{
		int j = 0;
		while (j < nSubTextLen && strText.at(i + j) == strSubText.at(j))
		{
			j++;
		}
		if (j == nSubTextLen)
		{
			return i;
		}
		int k = nSubTextLen - 1; // 最右匹配原则
		while (k >= 0)
		{
			if (strText.at(i + nSubTextLen) == strSubText.at(k))
			{
				break;
			}
			k--;
		}
		{
			k = k < 0 ? 0 : k;
			i += nSubTextLen - k - 1;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	String a = "hello world";
	String b = "wor";
	int nRet = SundaySearch(a, b);
	printf("nRet = %d ", nRet);
	getchar();
	return 0;
}