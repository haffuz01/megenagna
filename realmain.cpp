#include<iostream>
#include<string>        //needed for getline
#include<string.h>      //needed for strcmp
#include<ctime>         //adeed for initiating random number generator
#include<cstdlib>       //     >>
#include<fstream>       //to output the user data into a file

using namespace std;

struct user
{
    string name;
    string celebrity;
    int age;
    char gender;
    int dept;
    int personality[3];
    int hobbies[3];
    int dream_city;
};

struct user user[30];

//variables
int user_num=11,match_num=0,compatibility_score[30];
string hobbies[13]={"", "Reading", "Drawing", "Cooking", "Video Games", "Music", "Travel", "Dancing", "Photography", "Writing", "Shopping", "Swimming", "Working out"};
string personalities[13]={"", "Honest", "Dependable", "Polite", "Creative", "Organized", "Fun", "Caring", "Determined", "Loyal", "Flexible", "Tolerant", "Insightful"};
string cities[11]={"", "Paris", "London", "Moscow", "Dubai", "Singapore", "New York", "Istanbul", "Tokyo", "Seoul", "Shanghai"};
string depts[13]={"","Human Nutrition", "Chemical Engineering", "Food Engineering", "Civil Engineering", "Computer Engineering", "Electrical Engineering", "Computer Science", "Information Systen", "Information Technology", "Cyber Security", "Software Engineering", "Mechanical Engineering",};

inline void profile_fill(int num){          //this function accepts profile input from users
    cout<<"Name : ";
    cin.ignore();
    getline (cin,user[num].name);
    cout<<"Age :";
    cin>>user[num].age;
    while (cin.fail())
    {cout<<"Invalid age. Please Input correctly\n";                //I found this method to limit the input to only integers
    cin.clear();                                                   //I made some modifications so it fits our purpose
    cin.ignore(500,'\n');
    cin>>user[num].age;}
    cout<<"Gender :";
    cin>>user[num].gender;
    cout<<"\n\t----------------\nWhat do you study?\n\n";
    for (int i=1;i<7;i++){
        cout<<i<<". "<<depts[i];
        if (i == 2 || i==6 || i == 5) cout<<" \t ";
        else cout<<" \t\t ";
        cout<<i+6<<". "<<depts[i+6]<<endl;}
    cin>>user[num].dept;
}
inline void compatability_questions(int num){               //this function asks more questions used for compatibility matching
    cout<<"\n\t----------------\nWhat's your dream city?\n\n";
    for (int i=1;i<6;i++)
        cout<<i<<". "<<cities[i]<<" \t "<<i+5<<". "<<cities[i+5]<<endl;
    cin>>user[num].dream_city;
    cout<<"\n\t----------------\nHow would you describe your personality?\n\n";
    for (int i=1;i<7;i++){
        cout<<i<<". "<<personalities[i];
        if (i !=6) cout<<" \t ";
        else cout<<" \t\t ";
        cout<<i+6<<". "<<personalities[i+6]<<endl;}
    cout<<"\n**Hint: You can choose three"<<endl;
    for (int i=0;i<3;i++)
        cin>>user[num].personality[i];
    cout<<"\n\t----------------\nWhat do you like spending time on?\n\n";
    for (int i=1;i<7;i++){
        cout<<i<<". "<<hobbies[i]<<" \t "<<i+6<<". "<<hobbies[i+6]<<endl;}
    cout<<"**Hint: You can choose three"<<endl;
    for (int i=0;i<3;i++)
        cin>>user[num].hobbies[i];
    cout<<"\n\t----------------\nAnd finally, who's your favourite celebrity?\n(short name - Messi, Teddy, Will...)"<<endl;
    cin.ignore();
    getline (cin,user[num].celebrity);
}
void compatability_calc(int num){               //this function calculates compatibility with every user entry and puts the on one array
    int j=0;
    while (j<11)
    {
        if (user[num].gender!=user[j].gender){
            if (user[num].dream_city==user[j].dream_city)
                compatibility_score[j]+=3;
            if (user[num].age==user[j].age)
                compatibility_score[j]++;
            for (int m=0;m<3;m++){
                for (int l=0;l<3;l++){
                    if (user[num].personality[m]==user[j].personality[l])
                        compatibility_score[j]+=2;
                }
            }
            for (int m=0;m<3;m++){
                for (int l=0;l<3;l++){
                    if (user[num].hobbies[m]==user[j].hobbies[l])
                        compatibility_score[j]+=2;
                }
            }
            if (!strcmpi((user[num].celebrity).c_str(),(user[j].celebrity).c_str()))
            compatibility_score[j]+=4;
        }
    j++;
    }
}

inline int matchmaker(int comp[]){                  //this function figures out which index of the array has the highest value and returns that
    int index=0,largest=comp[0];
    for(int i=1;i<30;i++)
    {
        if (largest>=comp[i]){
            largest=largest;
            index=index;}
        else {
            largest=comp[i];
            index=i;}
    }
    if (largest==0)
        return 0;
    else return index;
}

inline int random_match(int num){                       //this one generates a random number and if that number maches the requirements it is returned
start:
    int j=0,random=0;
    while (j<50)
    {
        srand(time(0));
        random=rand()%11;
        if (user[num].gender!=user[random].gender && random!=0 && user[num].age!=0)
            return random;
        j++;
    }
    goto start;
}
void disp_profile(int num){             //this accepts an index and displays the components of the given index
    string pronoun;
    if (user[num].gender=='f')
        pronoun="She";
    else pronoun="He";
    cout<<"__--"<<user[num].name<<"--__"<<endl;
    cout<<user[num].age<<" years old"<<endl;
    cout<<pronoun<<"'s from "<<depts[user[num].dept]<<endl;
    cout<<pronoun<<" likes "<<hobbies[user[num].hobbies[0]]<<endl;
    cout<<"And "<<pronoun<<"'s a fan of "<<user[num].celebrity<<endl;
}

//I used this function to build some users for the algorithm to work on

void user_builder(int num, int ag, char gen, int dep, int persona0, int persona1, int persona2, int hob0, int hob1, int hob2, int drm){
    user[num].age=ag;
    user[num].gender=gen;
    user[num].dept=dep;
    user[num].personality[0]=persona0; user[num].personality[1]=persona1; user[num].personality[2]=persona2;
    user[num].hobbies[0]=hob0; user[num].hobbies[1]=hob1; user[num].hobbies[2]=hob2;
    user[num].dream_city=drm;
}

void save_user(int num)
{
    ofstream user_out;
    user_out.open("user_data.txt",ios::app);
    if (user_out.fail())
        cerr<<"An error ocured when trying to write to the file";
    user_out<<"--------------------------------------------"<<endl;
    user_out<<num<<"  |  "<<user[num].name;
    user_out<<" | "<<user[num].dream_city<<" | "<<user[num].celebrity;
    user_out<<" | "<<user[num].age<<" | "<<user[num].hobbies[0];
    user_out<<","<<user[num].hobbies[1]<<","<<user[num].hobbies[2];
    user_out<<" | "<<user[num].personality[0]<<","<<user[num].personality[1];
    user_out<<","<<user[num].personality[2]<<endl;
    user_out.close();
}

int main()
{
    //Built in Users
    user[1].name="Melat"; user[1].celebrity="Ronaldo";
    user_builder(1,22,'f',3,3,2,1,3,4,6,5);
    user[2].name="Betty"; user[2].celebrity="Shawn";
    user_builder(2,21,'f',2,3,5,7,8,6,4,9);
    user[3].name="Geremew"; user[3].celebrity="Teddy";
    user_builder(3,21,'m',4,1,3,5,2,7,4,1);
    user[4].name="Ruthi"; user[4].celebrity="Neymar";
    user_builder(4,23,'f',1,10,8,1,7,5,3,3);
    user[5].name="Yidnekachew"; user[5].celebrity="Einestien";
    user_builder(5,20,'m',6,4,6,9,9,6,10,2);
    user[6].name="Yared"; user[6].celebrity="Messi";
    user_builder(6,23,'m',11,5,4,3,5,6,8,7);
    user[7].name="Yordanos"; user[7].celebrity="Abdu Kiar";
    user_builder(7,19,'f',9,1,6,12,5,9,7,10);
    user[8].name="Asefa"; user[8].celebrity="Hamilton";
    user_builder(8,22,'m',7,11,9,7,12,6,3,8);
    user[9].name="Danawit"; user[9].celebrity="Trump";
    user_builder(9,24,'f',8,9,7,12,6,4,2,6);
    user[10].name="Daniel"; user[10].celebrity="Justin";
    user_builder(10,20,'m',5,1,3,7,12,9,1,2);

    int more_questions,verify,closer;

start:
    cout<<"---Welcome to Megenagna.com---\n* Where you find your DESTINY *\n"<<endl;
    cout<<"Since this is your first time here, Please setup your profile"<<endl;
    profile_fill(user_num);
    cout<<"Your profile has been saved.\nWould you like to answer some more questions?\nThis will help us find you the perfect match."<<endl;
    cout<<"1.Yes\t\t2.No(Random)"<<endl;
    cin>>more_questions;
    while (more_questions<1||more_questions>2){
        cout<<"Wrong Input, Please try again...";
        cin>>more_questions;
        }
    if (more_questions==2)
rematch1: match_num=random_match(user_num);
    else {
        compatability_questions(user_num);
        compatability_calc(user_num);
rematch2:compatibility_score[match_num]=0;
        match_num=matchmaker(compatibility_score);
        if (match_num==0){
            cout<<"Sorry, we couldn't find any match you."<<endl;
            return 0;}
    }
    cout<<"Based on your preference, Your match is :"<<endl;
    disp_profile(match_num);
    cout<<"1.Okay - Send my profile\n2.Next please"<<endl;

    cin>>verify;
    while (verify<1||verify>2){
        cout<<"Wrong Input, Please try again...";
        cin>>verify;
        }
    if (verify==2)
    {
        if (more_questions==2)
            goto rematch1;
        else
            goto rematch2;
    }
    else{
        cout<<"Your info has has been sent, Good luck!"<<endl;
        save_user(user_num);}
    cout<<"1.Restart\t\t2.Exit"<<endl;
    cin>>closer;
    while (closer<1||closer>2){
        cout<<"Wrong Input, Please try again...";
        cin>>closer;
        }
    if (closer==2)
        return 0;
    else {
        user_num++;
        goto start;}

}
