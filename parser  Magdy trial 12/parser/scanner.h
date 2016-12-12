#include <string>
#include <queue>
#include <vector>
using namespace std;

//Global variables
int tokenTypeNo = 0;
int tokenValueNo = 0;
vector<string> TokenType;
vector<string> TokenValue;

void advanceToken()
{
	tokenTypeNo++ ;
	tokenValueNo++ ;
}

bool TokenTypesFinished()
{
	if(tokenTypeNo == TokenType.size())
		return true;
	else
		return false;
}

bool TokenValuesFinished()
{
	if(tokenValueNo == TokenValue.size())
		return true;
	else
		return false;
}

string getTokenType()
{
	return TokenType[tokenTypeNo];
}

string getTokenValue()
{
	return TokenValue[tokenValueNo];
}

vector<string> TokenValueForTinyCLanguage(queue<string> q)
{
	vector<string> TokenValue;
	string QueueLine ;
	char token[200] = {};
	int j = 0 ;
	while(!q.empty())
	{
		QueueLine = q.front();
		q.pop();
		for (int i = 0; i < QueueLine.length(); i++)
		{   
			if (QueueLine[i] == ' ')
			{
				continue;
			}
			// line comment
			else if (QueueLine[i] == '{')
			{
				while (QueueLine[i] != '}')
				{
					QueueLine.erase(i,1);
				}
				QueueLine.erase(i,1);
				i--;
			}
			// number 
			else if (QueueLine[i] >= 48 && QueueLine[i] <= 57)
			{   
				while(i < QueueLine.length())
				{
					if (QueueLine[i] >= 48 && QueueLine[i] <= 57)
					{
						token[j++] = QueueLine[i++];
					}
					else
						break;
				}
				TokenValue.push_back(token);
						
				for (int k = 0; k < sizeof(token); k++) {
					token[k] = '\0';
				}
				i--; 
				j = 0;
			}
			// identifier or reserved word
			else if (((QueueLine[i] >= 65 && QueueLine[i] <= 90) || (QueueLine[i] >= 97 && QueueLine[i] <= 122) || (QueueLine[i] == 95) || (QueueLine[i] >= 48 && QueueLine[i] <= 57)))
			{   
				while(i < QueueLine.length())
				{
					if (((QueueLine[i] >= 65 && QueueLine[i] <= 90) || (QueueLine[i] >= 97 && QueueLine[i] <= 122) || (QueueLine[i] == 95) || (QueueLine[i] >= 48 && QueueLine[i] <= 57)))
					{   
						token[j++] = QueueLine[i++];
					}
					else
						break;
				}
			 	TokenValue.push_back(token);
				for (int k = 0; k < sizeof(token); k++) {
					token[k] = '\0';
				}
				i--; 
				j = 0;
			}
			// special symbol
			else if (QueueLine[i] == '+' || QueueLine[i] == '-' || QueueLine[i] == '*' || QueueLine[i] == '/' || QueueLine[i] == '=' || QueueLine[i] == '<' || QueueLine[i] == '(' || QueueLine[i] == ')' || QueueLine[i] == ';' || QueueLine[i] == ':')
			{           
						if (QueueLine[i] == ':')
						{
							TokenValue.push_back(":=");
							i++;
							for (int k = 0; k < sizeof(token); k++) {
								token[k] = '\0';
							}
							j = 0;
						}
						else
						{
							token[j] = QueueLine[i];
							TokenValue.push_back(token);
							for (int k = 0; k < sizeof(token); k++) {
								token[k] = '\0';
							}
							j = 0;
						}
			}
		}
	}
		
	return TokenValue;
}

string SpecialSymbolType(char SpecialSymbol)
{
	string type;
	switch (SpecialSymbol)
	{
		case '+' :
			type = "Plus Operator";
			break;
		case '-' :
			type = "Minus Operator";
			break;
		case '*' :
			type = "Multiply Operator";
			break;
		case '/' :
			type = "Divide Operator";
			break;
		case ';' :
			type = "SEMI";
			break;
		case '=' :
			type = "equal Operator";
			break;
		case '<' :
			type = "LessThan Operator";
			break;
		case '>' :
			type = "GreaterThan Operator";
			break;
		case '(' :
			type = "LeftBraket";
			break;
		case ')' :
			type = "RightBraket";
			break;
		case ':' :
			type = "Assignment Operator";
			break;
	}
	return type;
}

vector<string> TokenTypeForTinyCLanguage(vector<string> q)
{
	vector<string> TokenType;
	string token;
	string SymbolType;
	for(int i = 0; i < q.size(); i++)
	{
		token = q[i];
		if (token == "if" || token == "then" || token == "else" || token == "end" || token == "repeat" || token == "until" || token == "read" || token == "write")
			TokenType.push_back("reserved word");
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "=" || token == "<" || token == "(" || token == ")" || token == ";" || token == ":=")
		{
			SymbolType = SpecialSymbolType(token[0]);
			TokenType.push_back(SymbolType);
		}
		else
		{
			bool isnumber = true;
			for (int i = 0; i < token.length(); i++ )
			{
			
				if (!(token[i] >= 48 && token[i] <= 57))
				isnumber = false;
			}
			if (isnumber)
			TokenType.push_back("number");
			
			else
			{
				bool isidentifier = true;
				for (int i = 0; i < token.length(); i++)
				{
					if (i == 0)
					{
						if (!((token[i] >= 65 && token[i] <= 90) || (token[i] >= 97 && token[i] <= 122) || (token[i] == 95)) )
							isidentifier = false;
					}
					else if (!((token[i] >= 65 && token[i] <= 90)|| (token[i] >= 97 && token[i] <= 122)|| (token[i] == 95)|| (token[i] >= 48 && token[i] <= 57)))
						isidentifier = false;
				}
				if (isidentifier)
					TokenType.push_back("identifier");
			}
		}
	}
	return TokenType;
}

void scannerOutput(queue<string> Queue)
{
	TokenValue = TokenValueForTinyCLanguage(Queue);
	TokenType = TokenTypeForTinyCLanguage(TokenValue);
}