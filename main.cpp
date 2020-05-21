#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string names[]={"Chandler", "Joey", "Rachel", "Phoebe", "Monika", "Ross", "Jannice", "Julie"};

const string postArchive[]={"Hello", "Bye-Bye" ,"LoL", "How you doin'?", "Chick and Duck", "Du be da be da"};

const string subjects[]={"Sports", "Science", "Cooking", "Hobbies"};

const string forumTitle[]={"Programming","Movies","Gaming"};
int id=0;//, n;

//time for current date
time_t now = time(0);
tm* ltm = localtime(&now);


struct treeNode{
	string creator;
	treeNode *left;
	treeNode *right;
};


class List{
    private:
        string text;
        List* next;
};

class post{

private:
    int Post_number;
    string title;
    string creator;
    tm creationDate;
    string text;
public:
    post(){
        Post_number=id++;
        int index = rand() % 5;
        creator=names[index];

        index = rand() % 5;
        text=postArchive[index];
        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;
        cout<< "Post with number: " << Post_number << " title: " << title << " creator: " <<creator;
        cout<< " date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year <<" and text: " << text << " has been created" <<endl;
    }

    int getId(){
        return Post_number;
    }
    string getCreator(){
        return creator;
    }
    string getText(){
        return text;
    }
    void printPost(){
        cout<< "Post : " << Post_number << " title: " << title << " creator: " <<creator;
        cout<< " date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year <<" and text: " << text <<endl;
    }


    ~post(){

            cout<<"Post number:"<<Post_number<<" is about to be destroyed"<<endl;
    }

};



class thread{

private:
    string subject;
    string creator;
    tm creationDate;
    post** posts;
    int n=rand() % 10 +1;
public:

    //default constructor
    thread(){
        int index= rand() % 4;
        subject=subjects[index];
        index= rand() % 6;
        creator= names[index];

        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;

        posts= new post*[n];

        for (int i = 0; i < n; i++) {

            posts[i]=new post();
        }
        cout<<"Thread with subject: " <<subject<< " has just been created!" <<endl;
    }
    thread(string subjectIn){
        // n=(rand() % 10);
        // n=5;
        subject=subjectIn;
        int index= rand() % 6;
        creator= names[index];

        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;

        posts= new post*[n];

        for (int i = 0; i < n; i++) {

            posts[i]=new post();
        }
        cout<<"Thread with subject: " <<subject<< " has just been created!" <<endl;
    }

    post** getPosts(){
            return posts;
    }
    string getSubject(){
        return subject;
    }

    int getN(){
        return n;
    }

    void printThread(){
        cout<<"Thread subject is "<<subject<<" creator is "<<creator;
        cout<< " creation date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year<<endl;
        cout<<" and posts:"<<endl;
        for ( int i = 0; i < n; i++)

           posts[i]->printPost();
    }

    void printRandomPosts(){
        for (int i = 0; i < rand () %n; i++) {
            posts[i]->printPost();
        }
    }
    int findPostById(int id){
        for (int i = 0; i < n; i++) {
            if (id==posts[i]->getId()){
                posts[i]->printPost();
                return 1;
            }
        }
        return 0;
    }


    ~thread(){
        for(int i =0 ; i< n ; i++){
            delete  posts[i];
        }
        delete  posts;
        cout<<"Thread with subject: " <<subject<< " is about to be destroyed" <<endl;

    }

};


class forum{

private:
    string title;
    thread** threads;
    int n=rand() %10 +1;
public:
    //default constructor
    forum(){
        threads=new thread*[n];
        for (int i = 0; i < n; i++) {
            threads[i] = new thread;
        }
        cout<<"Forum with title: "<<title<<" has just been created!"<<endl;
    }

    //constructor with specific title
    forum(string titleIn){
        title=titleIn;

        threads=new thread*[n];
        int i=0;
        if (titleIn=="OOP" && n>=1) {
            threads[0]=new thread("Rules and useful info");
            i=1;
        }
        for ( ; i < n; i++) {
            threads[i] = new thread;
        }
        cout<<"Forum with title: "<<title<<" has just been created!"<<endl;
    }

    void printForum(){
        cout<<"Forum with title: "<<title<< " has threads with titles: "<<endl;
        for ( int i = 0; i < n; i++)
           cout<<threads[i]->getSubject()<<" ";
        cout<<endl;
    }

    int printThread(string threadIn){

        for (int i = 0; i < n; i++) {
            if (threadIn==threads[i]->getSubject()){
                threads[i]->printThread();
                return 1;
            }
        }
        return 0;
    }

    void printRandomPosts(){
        cout<<"Printing random posts: "<<endl;
        // int random=rand() % n;
        for (int i = 0; i < rand() % n ; i++) {
            threads[i]->printRandomPosts();
        }
        cout<<endl;
    }
    int findPostById(int id){
        for (int i = 0; i < n; i++) {
            if (threads[i]->findPostById(id)){
                // threads[i]->printPost();
                cout<<"Post found and it's above^ "<<endl;
                return 1;
            }
        }
        cout<<"Post not found."<<endl;
        return 0;
    }

    ~forum(){
            for(int i =0 ; i< n ; i++){
                delete  threads[i];
            }
            delete  threads;
        cout<<"Forum with title "<<title<<" is about to be destroyed"<<endl;
    }
};


class btree{
    private:
        treeNode* root;
        List myList;

    public:
        btree(){

        }
        btree(thread &threadIn){
            post** posts=threadIn.getPosts();
            int n=threadIn.getN;
        }


};




int main(){

    srand (time(0));
    forum forum1("OOP");
    forum1.printForum();
    if (forum1.printThread("Rules and useful info")==0){
        cout<<"Could not find Thread"<<endl;
    }
    forum1.printRandomPosts();
    forum1.findPostById(0);
    return 0;
}
