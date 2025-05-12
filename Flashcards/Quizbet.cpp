#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

const int MAX_CARDS = 999, MAX_Q = 400;
struct Card { string t, d; };
struct Q    { string p, o[4]; int c; };

vector<int> buildShuffleOrder(int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;

    static std::default_random_engine rng(
        static_cast<unsigned>(time(nullptr)));
    shuffle(order.begin(), order.end(), rng);
    return order;
}
void loadC(Card a[], int &n, const string &f){
    ifstream in(f); n = 0; string l;
    while(getline(in,l)&&n<MAX_CARDS){
        size_t p=l.find("::"); if(p==string::npos) continue;
        a[n++]={l.substr(0,p),l.substr(p+2)};
    }
}
void loadQ(Q a[], int &n, const string &f){
    ifstream in(f); n = 0; string l;
    while(getline(in,l)&&n<MAX_Q){
        size_t p[6]; p[0]=l.find("::"); if(p[0]==string::npos) continue;
        bool bad=false;
        for(int i=1;i<5;i++){ p[i]=l.find("::",p[i-1]+2); if(p[i]==string::npos){bad=true;break;}}
        if(bad) continue;
        a[n].p = l.substr(0,p[0]);
        for(int i=0;i<4;i++) a[n].o[i] = l.substr(p[i]+2,p[i+1]-p[i]-2);
        char L = l[p[4]+2]; a[n].c = (L=='A'?0:L=='B'?1:L=='C'?2:3);
        ++n;
    }
}
void flash(Card cards[], int count) {
    auto order = buildShuffleOrder(count);

    cout << "\n--- Flashcards (random order) ---\n"
         << "Press ENTER to flip or q + ENTER to quit.\n";

    for (int idx : order) {
        cout << "\nTerm: " << cards[idx].t << "\n> ";
        string in;
        getline(cin, in);
        if (in == "q" || in == "Q" || in == "0") break;
        cout << "Definition: " << cards[idx].d << '\n';
    }
}
void mc(Card cards[], int count) {
    auto order = buildShuffleOrder(count);
    cout << "\n--- Multiple Choice (random order) ---\n";

    int correct = 0;
    for (int i = 0; i < count; ++i) {
        int idx = order[i];

        string corr = cards[idx].d;
        string opt[4];
        int pos = rand() % 4;
        opt[pos] = corr;
        for (int j = 0; j < 4; ++j)
            if (j != pos) {
                int r;
                do { r = rand() % count; } while (cards[r].d == corr);
                opt[j] = cards[r].d;
            }

        cout << "\n(" << i + 1 << '/' << count << ") Define: "
             << cards[idx].t << '\n';
        for (int k = 0; k < 4; ++k) cout << k + 1 << ") " << opt[k] << '\n';

        cout << "Answer (1-4, q to quit): ";
        string in; getline(cin, in);
        if (in == "q" || in == "Q" || in == "0") break;

        int ans = stoi(in);
        if (opt[ans - 1] == corr) { ++correct; cout << "✅\n"; }
        else                       { cout << "❌ " << corr << '\n'; }
    }
    cout << "\nScore: " << correct << " / " << count << '\n';
}
void written(Card cards[], int count) {
    auto order = buildShuffleOrder(count);
    cout << "\n--- Written Test (random order) ---\n";

    int good = 0;  string ans;
    for (int i = 0; i < count; ++i) {
        int idx = order[i];
        cout << "\n(" << i + 1 << '/' << count << ") Define: "
             << cards[idx].t << "\nYour answer (q=quit): ";
        getline(cin, ans);
        if (ans == "q" || ans == "Q" || ans == "0") break;

        if (ans == cards[idx].d) { ++good; cout << "✅\n"; }
        else                     { cout << "❌ " << cards[idx].d << '\n'; }
    }
    cout << "\nTotal correct: " << good << '\n';
}
void practice(Q a[], int n, int ask) {

    int idx[MAX_Q];
    for (int i = 0; i < n; ++i) idx[i] = i;
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(idx[i], idx[j]);
    }

    bool correct[MAX_Q] = {false};
    int answered = 0;

    for (int i = 0; i < ask; ++i) {
        const Q &q = a[idx[i]];
        cout << "\nQ" << i + 1 << ") " << q.p << '\n';
        for (int k = 0; k < 4; ++k)
            cout << k + 1 << ") " << q.o[k] << '\n';

        cout << "(0 or q = quit) Answer: ";
        string in;
        getline(cin, in);

        if (in == "q" || in == "Q" || in == "0") {
            ask = i;                       
            break;
        }

        int ans = 0;
        try { ans = stoi(in); } catch (...) { ans = 0; }
        if (ans < 1 || ans > 4) {
            cout << "Invalid entry; please answer 1-4 next time.\n";
            --i;                           
            continue;
        }

        correct[i] = (ans - 1 == q.c);
        ++answered;
    }

    cout << "\n--- ANSWER KEY ---\n";
    int score = 0;
    for (int i = 0; i < answered; ++i) {
        const Q &q = a[idx[i]];
        cout << "Q" << i + 1 << ") " << q.o[q.c]
             << " (" << (correct[i] ? "✔" : "✖") << ")\n";
        if (correct[i]) ++score;
    }
    cout << "\nScore " << score << " / " << answered
         << " (" << (answered ? score * 100 / answered : 0) << "%)\n";
}

int pick() {  
    cout << "========= AWS Certification Library =========\n"
         << " 1) Cloud Practitioner\n"
         << " 2) AI Practitioner\n"
         << " 3) Solutions Architect - Associate\n"
         << " 4) Solutions Architect - Professional\n"
         << " 5) Developer - Associate\n"
         << " 6) SysOps Administrator - Associate\n"
         << " 7) DevOps Engineer - Professional\n"
         << " 8) Data Engineer - Associate\n"
         << " 9) Machine Learning Engineer - Associate\n"
         << "10) Security - Specialty\n"
         << "11) Advanced Networking - Specialty\n"
         << "12) Data Analytics - Specialty\n"
         << "13) Machine Learning - Specialty\n"
         << " 0) Exit\n"
         << "---------------------------------------------\n"
         << "Choice: ";
    int c;
    cin >> c;
    cin.ignore();       
    return c ? c - 1 : -1;   
}
int main(){
    srand((unsigned)time(0));
    const string files[]={
        "data/AWSCloudPractitioner.txt","data/AWSAIPractitioner.txt",
        "data/AWSSolutionsArchitectAssociate.txt","data/AWSSolutionsArchitectProfessional.txt",
        "data/AWSDeveloperAssociate.txt","data/AWSSysOpsAdministrator.txt",
        "data/AWSDevOpsProfessional.txt","data/AWSDataEngineerAssociate.txt",
        "data/AWSMachineLearningEngineerAssociate.txt","data/AWSSecuritySpecialty.txt",
        "data/AWSAdvancedNetworkingSpecialty.txt","data/AWSDataAnalyticsSpecialty.txt",
        "data/AWSMachineLearningSpecialty.txt"
    };
    const string qf[]={
        "questions/AWSCloudPractitioner_questions.txt","questions/AWSAIPractitioner_questions.txt",
        "questions/AWSSolutionsArchitectAssociate_questions.txt","questions/AWSSolutionsArchitectProfessional_questions.txt",
        "questions/AWSDeveloperAssociate_questions.txt","questions/AWSSysOpsAdministrator_questions.txt",
        "questions/AWSDevOpsProfessional_questions.txt","questions/AWSDataEngineerAssociate_questions.txt",
        "questions/AWSMachineLearningEngineerAssociate_questions.txt","questions/AWSSecuritySpecialty_questions.txt",
        "questions/AWSAdvancedNetworkingSpecialty_questions.txt","questions/AWSDataAnalyticsSpecialty_questions.txt",
        "questions/AWSMachineLearningSpecialty_questions.txt"
    };
    const int base[]={65,50,65,75,75,65,75,65,65,65,65,65,65};
    int id=pick(); if(id<0) return 0;
    Card c[MAX_CARDS]; int cn=0; loadC(c,cn,files[id]);
    Q    q[MAX_Q];    int qn=0; loadQ(q,qn,qf[id]);
    int goal=base[id]*3; if(goal>qn) goal=qn;
    int ch;
    do{
        cout<<"\n1) Flash\n "
            <<"2) MC\n "
            <<"3) Written\n "
            <<"4) Practice\n "
            <<"5) Exit\n";
        cin>>ch; cin.ignore();
        if(ch==1) flash(c,cn);
        else if(ch==2) mc(c,cn);
        else if(ch==3) written(c,cn);
        else if(ch==4){ if(qn) practice(q,qn,goal); else cout<<"No questions.\n"; }
    }while(ch!=5);
    return 0;
}
