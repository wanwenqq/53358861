#include <string>

using namespace std;






class MMTrace
{
	public:
		MMTrace( const char*  &name);
		~MMTrace();
		


		void Debug( const char*  &msg);

		static bool m_bTraceIsAlive;


	private:
		string*	 m_strFunctionName;
};
