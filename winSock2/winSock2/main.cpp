#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::flush;
using std::locale;
#pragma comment(lib,"ws2_32.lib")





int main(void) {

    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    int lineCount = 0;
    int rowCount = 0;
    struct hostent* host;
    locale local;
    char buffer[10000];
    int i = 0;
    int nDataLength;
    string website_HTML;

    cout << "Please input website: " << flush;
    // website url
    //string url = "www.google.com";
    string url = "";
    //cin >> url;
    getline(cin, url);

    //HTTP GET
    string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";


    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed.\n";
        system("pause");
        //return 1;
    }

    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    host = gethostbyname(url.c_str());

    SockAddr.sin_port = htons(80);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
        cout << "Could not connect";
        system("pause");
        //return 1;
    }

    // send GET / HTTP
    send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

    // recieve html
    while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
        int i = 0;
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

            website_HTML += buffer[i];
            i += 1;
        }
    }

    closesocket(Socket);
    WSACleanup();

    // Display HTML source 
    cout << website_HTML;

    // pause
    cout << "\n\nPress ANY key to close.\n\n";
    cin.ignore(); cin.get();

    cin.clear();
    cin.ignore();


    return 0;
}