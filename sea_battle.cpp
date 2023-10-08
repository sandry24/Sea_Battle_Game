#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define pb push_back
#define mp make_pair

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

int random_Number(int min, int max){
    std::uniform_int_distribution<> random{min, max};
    return random(mersenne);    
}

void output_Grid(vector<vector<string>> a){
    cout << "=============================================\n" << "  || A | B | C | D | E | F | G | H | I | J ||\n" << "=============================================\n"; 
    for(int i = 0; i < 10; i++){
        if(i != 9)
            cout << i+1 << " ||";
        else
            cout << i+1 << "||";
        for(int j = 0; j < a.size(); j++){
            cout << a[i][j] << '|';
        }
        cout << '|' << '\n';
        if(i != 9)
            cout << "==||---|---|---|---|---|---|---|---|---|---||\n";
        else
            cout << "=============================================\n";
    }
}

bool check_Input(string ans){
    if(ans.size() != 2 && ans.size() != 3)
        return false;
    if(ans.size() == 3 && ((ans[0] != '1') || (ans[1] != '0') || (ans[2] < 65) || (ans[2] > 74)))
        return false;
    if(ans.size() == 2 && ((ans[0] < 49) || (ans[0] > 57) || (ans[1] < 65) || (ans[1] > 74)))
        return false;
    return true;
}

int return_Winner(vector<vector<string>> a, vector<vector<string>> b){
    bool win = true;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            if(a[i][j] == " # ")
                win = false;
    }
    if(win)
        return 1;
    win = true;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            if(b[i][j] == " # ")
                win = false;
    }
    if(win)
        return 0;
    return -1;
}

bool check_Adjacent(vector<vector<string>> a, int x, int y, int type = 1){
    string pat = " # ";
    if(type == 2)
        pat = " X ";
    if(a[x][y] == pat)
        return false;
    if(x < 9 && a[x+1][y] == pat)
        return false;
    if(x > 0 && a[x-1][y] == pat)
        return false;
    if(y < 9 && a[x][y+1] == pat)
        return false;
    if(y > 0 && a[x][y-1] == pat)
        return false;
    return true;
}

bool check_Destroyed(vector<vector<string>> a){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(a[i][j] == " X "){
                if(!check_Adjacent(a, i, j)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool just_hit = false, more_hit = false;
pi index_hit, second_index_hit;

pi leftright_alg(pi second_index_hit, vector<vector<string>> &a){
    pi ans;
    int x = index_hit.first;
    int y = index_hit.second;
    for(int i = y; i < 10; i++){
        if(a[x][i] == " M ")
            break;
        if(a[x][i] == "   " || a[x][i] == " # "){
            ans = make_pair(x, i);
            return ans;
        }
    }
    for(int i = y; i >= 0; i--){
        if(a[x][i] == " M ")
            break;
        if(a[x][i] == " # " || a[x][i] == "   "){
            ans = make_pair(x, i);
            return ans;
        }
    }
}

pi updown_alg(pi second_index_hit, vector<vector<string>> &a){
    pi ans;
    int x = index_hit.first;
    int y = index_hit.second;
    for(int i = x; i < 10; i++){
        if(a[i][y] == " M ")
            break;
        if(a[i][y] == "   " || a[i][y] == " # "){
            ans = make_pair(i, y);
            return ans;
        }
    }
    for(int i = x; i >= 0; i--){
        if(a[i][y] == " M ")
            break;
        if(a[i][y] == " # " || a[i][y] == "   "){
            ans = make_pair(i, y);
            return ans;
        }
    }
}

pi just_hit_alg(pi index_hit, vector<vector<string>> &a){
    int move; pi ans;
    int x = index_hit.first;
    int y = index_hit.second;
    while(true){
        move = random_Number(1, 4);
        if(move == 1){
            if(x != 0 && a[x-1][y] != " M "){
                ans = make_pair(index_hit.first-1, index_hit.second);
                return ans;
            }
        } else if(move == 2){
            if(y != 9 && a[x][y+1] != " M "){
                ans = make_pair(index_hit.first, index_hit.second+1);
                return ans; 
            }
        } else if(move == 3){
            if(x != 9 && a[x+1][y] != " M "){
                ans = make_pair(index_hit.first+1, index_hit.second);
                return ans;
            }
        } else {
            if(y != 0 && a[x][y-1] != " M "){
                ans = make_pair(index_hit.first, index_hit.second-1);
                return ans;
            }
        }
    }
    ans = make_pair(-1, -1);
    return ans;
}

bool leftright = false, updown = false;

int bot_move(vector<vector<string>> &a){
    string ans; int x, y;
    x = random_Number(0, 9);
    y = random_Number(0, 9);
    while(a[x][y] == " M " || a[x][y] == " X " || !check_Adjacent(a, x, y, 2)){
        x = random_Number(0, 9);
        y = random_Number(0, 9); 
    }
    if(just_hit){
        pi ans = just_hit_alg(index_hit, a);
        if(ans.first != -1){
            x = ans.first;
            y = ans.second;
        }

    }
    if(more_hit){
        pi ans;
        if(leftright){
            ans = leftright_alg(index_hit, a);
            x = ans.first;
            y = ans.second;
        } else {
            ans = updown_alg(index_hit, a);
            x = ans.first;
            y = ans.second;
        }
    }
    char c = y + 65;
    string s = to_string(x+1) + c;
    cout << '\n';
    cout << "The computer chose: " << s << '\n';
    if(a[x][y] == "   "){
        cout << "Your opponent missed!\n";
        a[x][y] = " M ";
        cout << '\n';
        return 0;
    } else {
        a[x][y] = " X ";
        if(!check_Destroyed(a)){
            cout << "Your opponent hit your boat!\n";
            if(just_hit){
                more_hit = 1;
                just_hit = 0;
                if(index_hit.first == x-1 || index_hit.first == x+1)
                    updown = true;
                else
                    leftright = true;
            } else if(!more_hit){
                just_hit = 1;
            }
            index_hit.first = x;
            index_hit.second = y;
        } else {
            cout << "Your opponent destroyed your boat!\n";
            just_hit = false; more_hit = 0; updown = false; leftright = false; 
        }
        cout << '\n';
        return 1;
    }
}

int player_move(vector<vector<string>> &b, vector<vector<string>> &c){
    string ans; int x, y;
    cout << "Type in your guess(ex. 5F): ";
    cin >> ans;
    bool check1 = false;
    while(!check1){
        check1 = true;
        while(!check_Input(ans)){
            cout << "Please type in a valid guess(ex. 5F): ";
            cin >> ans;
        }
        x = ans[0] - 49;
        y = ans[1] - 65;
        if(ans.size() == 3){
            x = 9;
            y = ans[2] - 65;
        }
        if(b[x][y] == " X " || b[x][y] == " M "){
            cout << "You have already chosen this place before!\n";
            cout << "Please type in a valid guess(ex. 5F): ";
            cin >> ans;
            check1 = 0;
        }
    }
    cout << '\n' << '\n';
    if(b[x][y] == "   "){
        cout << "You missed!\n";
        b[x][y] = " M ";
        c[x][y] = " M ";
        cout << '\n';
        return 0;
    } else if(b[x][y] == " # "){
        b[x][y] = " X ";
        c[x][y] = " X ";
        if(!check_Destroyed(b)){
            cout << "You hit a boat!\n";
        } else {
            cout << "You destroyed a boat!\n";
        }
        cout << '\n';
        return 1;
    }
}

vector<string> possible(vector<vector<string>> a, int x, int y, int size){
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<string> possible_ans;
    for(int i = 0; i < 4; i++){
        bool flag = 1;
        int newx = x, newy = y;
        for(int j = 1; j < size; j++){
            newx += dx[i];
            newy += dy[i];
            if(newx < 0 || newy < 0 || newx > 9 || newy > 9){
                flag = 0;
                break;
            }
            if(!check_Adjacent(a, newx, newy)){
                flag = 0;
                break;
            }
        }
        if(flag){
            char c = newy + 65;
            string s = to_string(newx+1) + c;
            possible_ans.pb(s);
        }
    }
    return possible_ans;
}

void clear_boards(vector<vector<string>> &a, vector<vector<string>> &b, vector<vector<string>> &c){
    a = b = c = vector<vector<string>>(10, vector<string>(10, "   "));
}

void input_Boats_bot(vector<vector<string>> &b, vector<string> boats){
    cout << "Generating the bot's grid.\n";
    bool check1 = false;
    int x, y, y1, x1;
    vector<string> possible_ans;
    for(int i = 0; i < 10; i++){
        check1 = false;
        while(!check1){
            x = random_Number(0, 9);
            y = random_Number(0, 9);
            check1 = true;
            if(!check_Adjacent(b, x, y))
                check1 = false;
            possible_ans = possible(b, x, y, (int)boats[i].size());
            if(possible_ans.size() == 0)
                check1 = false;
        }
        int element = random_Number(0, possible_ans.size()-1);
        string elem = possible_ans[element];
        x1 = elem[0] - 49;
        y1 = elem[1] - 65;
        if(elem.size() == 3){
            x1 = 9;
            y1 = elem[2] - 65;
        }
        if(x1 == x){
            for(int i = min(y, y1); i <= max(y, y1); i++)
                b[x][i] = " # ";
        } else {
            for(int i = min(x, x1); i <= max(x, x1); i++)
                b[i][y] = " # ";
        }
    }
    cout << '\n';
    cout << "Done!\n";
    cout << '\n';
}

void input_Boats(vector<vector<string>> &a, vector<string> boats){
    string ans, ans2;
    int x, y, x1, y1;
    vector<string> possible_ans;
    bool check1 = false;
    for(int index = 0; index < 10; index++){
        check1 = false;
        while(!check1){
            cout << "Choose the starting position on the grid for the following boat(ex. 3C): " << boats[index] << '(' << boats[index].size() << ')' << '\n';
            cin >> ans;
            while(!check_Input(ans)){
                cout << "Please enter a valid place(ex. 3C): \n";
                cin >> ans; 
            }
            check1 = true;
            x = ans[0] - 49;
            y = ans[1] - 65;
            if(ans.size() == 3){
                x = 9;
                y = ans[2] - 65;
            }
            if(!check_Adjacent(a, x, y)){
                cout << "Two boats cant be next to each other!\n";
                cout << "Please enter a valid place(ex. 3C): \n";
                check1 = false;
                continue;
            }
            possible_ans = possible(a, x, y, (int)boats[index].size());
            if(possible_ans.size() == 0){
                cout << "Not possible to build a boat of size " << boats[index].size() << " from this point!\n";
                cout << "Please enter a valid place(ex. 3C): \n";
                check1 = false;
                continue; 
            }
        }
        if(boats[index].size() != 1){
            check1 = false;
            while(!check1){
                cout << "Choose the ending position on the grid for the following boat(ex. 3C): " << boats[index] << '(' << boats[index].size() << ')' << '\n';
                cout << "Your starting position: " << ans << '\n';
                cout << "Possible answers are: ";
                for(auto i : possible_ans)
                    cout << i << ' ';
                cout << '\n';
                cin >> ans2;
                while(!check_Input(ans2)){
                    cout << "Please enter a valid place(ex. 3C): \n";
                    check1 = false;
                    continue;
                }
                check1 = true;
                x1 = ans2[0] - 49;
                y1 = ans2[1] - 65;
                if(ans.size() == 3){
                    x1 = 9;
                    y1 = ans2[2] - 65;
                }
                if(find(possible_ans.begin(), possible_ans.end(), ans2) == possible_ans.end()){
                    cout << "Invalid place\n";
                    check1 = false;
                    continue;
                }
            }
        } else {
            x1 = x;
            y1 = y;
        }
        if(x1 == x){
            for(int i = min(y, y1); i <= max(y, y1); i++)
                a[x][i] = " # ";
        } else {
            for(int i = min(x, x1); i <= max(x, x1); i++)
                a[i][y] = " # ";
        }
        output_Grid(a);
    }
}

void solve(){
    vector<vector<string>> a, b, c;
    vector<string> boats = {"#", "#", "#", "#", "##", "##", "##", "###", "###", "####"};
    cout << "Start game? Y/N\n";
    char ans; cin >> ans;
    int hit_player = 0, hit_bot = 0;
    while(ans == 'Y'){
        clear_boards(a, b, c);
        output_Grid(a);
        cout << '\n';
        cout << "You have: ";
        for(auto i : boats)
            cout << i << ' ';
        cout << '\n';
        input_Boats(a, boats);
        //input_Boats_bot(a, boats);
        cout << '\n';
        input_Boats_bot(b, boats);
        //output_Grid(b);
        while(return_Winner(a, b) == -1){
            if(hit_bot == 0)
                hit_player = player_move(b, c);
            if(return_Winner(a, b) != -1){
                cout << "Your opponent overview grid: \n";
                output_Grid(c);
                cout << "Your grid: \n";
                output_Grid(a);
                break;
            }
            if(hit_player == 0)
                hit_bot = bot_move(a);
            cout << "Your opponent overview grid: \n";
            output_Grid(c);
            cout << "Your grid: \n";
            output_Grid(a);
        }
        if(return_Winner(a, b) == 0){
            cout << "YOU WON!\n" << '\n';
        } else 
            cout << "YOU LOST!\n" << '\n';
        cout << "Continue? Y/N\n";
        cin >> ans;
    }
/*   
=============================================
  || A | B | C | D | E | F | G | H | I | J ||
=============================================
1 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
2 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
3 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
4 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
5 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
6 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
7 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
8 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
9 ||   |   |   |   |   |   |   |   |   |   ||
==||---|---|---|---|---|---|---|---|---|---||
10||   |   |   |   |   |   |   |   |   |   ||
=============================================
*/
}

int main()
{
    //ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}