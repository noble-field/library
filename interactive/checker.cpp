//-------------------------------------------------
//--Interactive Judge Library
//-------------------------------------------------

#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>
#include <ctype.h>

class Interactive {
private:
	const char *fail_msg = "-1\n";
	static constexpr int BUF_SIZE = 512;
	char buf[BUF_SIZE+1];
	char *ip, *iend;
	int in[2], out[2];
	int nqueries;
	std::chrono::time_point<std::chrono::steady_clock> start;

	inline bool minus(char c){return c=='-';}
    inline int cnum(char c){return c-'0';}
    inline int numc(int c){return c+'0';}
	inline bool bounds_check(){
		if (ip >= iend){
			fprintf(stderr, "System: Out of Bounds.\n");
			reply(fail_msg);
			exit(EXIT_FAILURE);
			// return false;
		}
		return true;
	}
public:
	Interactive(int argc, char **argv):nqueries(0){
		if (argc != 2){
			fprintf(stderr, "System: Invalid Argments.\n");
			exit(EXIT_FAILURE);
		}
		pipe(in); pipe(out);
		
		pid_t pid = 0;
		pid = fork();
		if (pid == 0){
			dup2(out[0], STDIN_FILENO);
			dup2(in[1], STDOUT_FILENO);
			prctl(PR_SET_PDEATHSIG, SIGTERM);
			execl(argv[1], argv[1], NULL);
			// If failing to execute
			fprintf(stderr, "System: Can't execute \"%s\"\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		close(out[0]); close(in[1]);
		ip = iend = NULL;
		start = std::chrono::steady_clock::now();
	}
	~Interactive(){
		auto stop = std::chrono::steady_clock::now();
		uint32_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
		fprintf(stderr, "Execution Time: %u ms\n", elapsed);
	}
	template<typename ... Args>
	void reply(const char *format, Args const & ... args){
		fprintf(stderr, "Judge: ");
		fprintf(stderr, format, args ...);
		fputc('\n', stderr);
		dprintf(out[1], format, args ...);
		fsync(out[1]);
	}
	void recv(){
		ssize_t sz = read(in[0], buf, BUF_SIZE);
		if (buf[sz-1] == '\n') buf[sz-1] = '\0', iend = buf+sz;
		else buf[sz] = '\0', iend = buf+sz+1;
		ip = buf;
		fprintf(stderr, "Client: ");
		fprintf(stderr, "%s\n", buf);
	}
	void recv_line(){
		char *p = buf;
		while(p < buf+BUF_SIZE){
			ssize_t sz = read(in[0], p, BUF_SIZE-(p-buf));
			for(size_t i=0; i<sz; i++){
				if (*p == '\n'){
					*(p++) = '\0';
					break;
				}
				p++;
			}
			if (*(p-1) == '\0') break;
		}
		ip = buf; iend = p;
		fprintf(stderr, "Client: ");
		fprintf(stderr, "%s\n", buf);
	}
	char read_char(){
		while(bounds_check() && isspace(*ip)) ip++;
		return *ip++;
	}
	void read_str(std::string &s){
		std::string t="";
        while(bounds_check() && isspace(*ip)) ip++;
        while(bounds_check() && !isspace(*ip)) t+=*ip++;
        s.swap(t);
	}
	template<typename T=int>
	T read_int(){
		bool s; T ret=0;
        while(bounds_check() && !isdigit(*ip) && !minus(*ip)) ip++;
        if (bounds_check() && s=minus(*ip)) ip++;
        while(bounds_check() && isdigit(*ip)) ret=ret*10+cnum(*ip++);
        return s?-ret:ret;
	}
	template<typename T=int>
	std::vector<T> read_int_array(){
		std::vector<T> ret;
		while(ip < iend){
			while(ip < iend && (isspace(*ip)||*ip=='\0')) ip++;
			if (ip == iend) break;
			ret.push_back(read_int<T>());
		}
		return ret;
	}
	void judge(bool accepted){
		if (accepted) fprintf(stdout, "Accepted\n");
		else fprintf(stdout, "Wrong Answer\n");
	}
	void set_query_limit(int limit){nqueries = limit;}
	int consume_query(){
		if (--nqueries < 0){
			judge(false);
			fprintf(stderr, "System: Query Limit Exceeds.\n");
			reply(fail_msg);
			exit(EXIT_FAILURE);
		}
	}

	Interactive& operator>>(char &a){a=read_char();return *this;}
	Interactive& operator>>(std::string &a){read_str(a);return *this;}
	template<typename T=int>
	Interactive& operator>>(T &a){a=read_int<T>();return *this;}
};
