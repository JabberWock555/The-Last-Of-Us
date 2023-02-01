#include <iostream>
#include <random>
using namespace std;

//-----------------------------------------------------
random_device rd;
mt19937 gen(rd());
int RandomNo(int min, int max){
  uniform_int_distribution<int>dist(min, max);
  return dist(gen);
}

//Enemy Class
class Enemy
{
private:
int EnemyHealth;
int EnemyDamage;
  
public:
Enemy(int _Health, int _Damage){
  EnemyHealth = _Health;
  EnemyDamage = _Damage;
}
//Getter
int Get_Health(){
  return EnemyHealth;
}
int Get_Damage(){
  return EnemyDamage;
}

//Setter


bool Is_Alive(){
  if (EnemyHealth <= 0 ){
    return false;
  }else {
    return true;
  }
}
void Damage(int x){
  EnemyHealth = EnemyHealth - x;
}
};


//Player Class
class Player
{

private:
string PlayerName;
int Health;
int MeleeDamage;
int RangedDamage;
int HealPower =  RandomNo(5, 10);
int MaxHealth;
public:

Player(){
  cout<<"\nEnter a Name for your Player.\n";
  cin>>PlayerName;
  
}
//Getter
string Name(){
  return PlayerName;
}
int Get_Health(){
  return Health;
}




//Setter
void Set_Health(int x){
  Health = x;
}
void Set_MeleeDamage(int x){
  MeleeDamage = x;
}
void Set_RangedDamage(int x){
  RangedDamage = x;
}
void Set_HealPower(int x){
  HealPower += x;
}
void Set_MaxHealth(int x){
  MaxHealth = x;
}

//Actions
void Heal(){
  if(Health > 0 && Health < MaxHealth){
  Health += HealPower;
    }
  else{
    cout<<"\nPlayer Health is full!"<<endl;
    }
}
void Damage(int x){
  Health = Health - (x);
}  

int Attack(int level, Enemy *ptr){
  if(!RandomNo(0, 9)){
    cout<<PlayerName<<" Special Power\n";
    switch(RandomNo(0,level)){
      case 1:
      cout<<"Activating CRITICAL PUNCH\n";
      return 50;
      break;

      case 2: 
      cout<<"Activating BLOCKING SHIELD\n";
        Health += ptr -> Get_Damage();
      return 0;
      break;

      case 3:
      cout<<"Activating Life Steal\n";
      ptr -> Damage(ptr -> Get_Health());
      return 0;
      break;

      case 4:
      cout<<"Activating RAGED ATTACK\n";
      return 50;
      break;

      Default:
        break;
      
    }
    cout<<"Special Ability has not been acquired\n";
  }
  
    switch(RandomNo(1,2)){
      case 1:
      cout<<"Melee attack by "<<PlayerName<<endl;
      return MeleeDamage;
      break;
      case 2:
      cout<<"Range Attack by "<<PlayerName<<endl;
      return RangedDamage;
      break;
    
  }
}

bool IsAlive(){
  if (Health <= 0){
    return false;
  }else {
    return true;
  }
}
};

//Boss Character class
class Boss: public Enemy
{
private:
int Health;
int MaxHealth;
int MeleeDamage;
int RangedDamage;
int HealPower;


public: 
Boss(int _Health , int _Damage, int _HealPower) : Enemy( _Health , _Damage){
  RangedDamage = _Damage * 20;
  MeleeDamage = _Damage;
  HealPower = _HealPower;
  MaxHealth = _Health;
  cout<<"The Shambler has been Spawned!!";
  cout<<"";
}

int acid_Attack(){
  cout<<"OHH! The Shambler an Acid Bomb!";
  return 150;
}
int wall_Smash(){
  cout<<"The Shambler smashed you on the wall!";
  return 100;
}

int Attack(){
  if (!RandomNo(0,2)){
  switch(RandomNo(0,1)){
    case 0:
    return acid_Attack();
    break;

    case 1:
    return wall_Smash();
    break;

    Default: break;
    }
  }
  
    switch(RandomNo(0,1)){
      case 0: 
      return MeleeDamage;
      break;

      case 1:
      return RangedDamage;
      break;

      
    }

}

void Life_Revival(){
  if(Health < 20){
    cout<<"The Shambler revived its Health\n";
    Health = MaxHealth; 
  }
}

void Life_Suck(int x){
  cout<<"The Shambler absorbed your half Health!" ;
  Health = Health + (x/2);
}

void Healing(Player *ptr){
if (!RandomNo(0,5)){
  switch(RandomNo(0,1)){
    case 0:
    Life_Revival();
    break;

    case 1:
    Life_Suck(ptr -> Get_Health());
      ptr -> Damage((ptr -> Get_Health())/2);
    break;

    Default: break;
 
    }
  }
else{
  Health += HealPower;
  cout<<"The Shambler Health: "<<Health<<endl;
}
    
}

bool is_Attacking(){
  if (RandomNo(0, 2) != 0)
      return true;
    else
      return false;
}

};



//Game Setup
class GameSetup
{
private:
char input;
Player *Player;
Enemy *Zombie;
Boss *Boss;
int LevelNo = 1;
int ZombieCount;

bool PlayerInput(){
        cout<<" \nPress 'A' to Attack\n";
        cout<<" \nPress 'H' to Heal\n";
        cin >> input;
        if (input == 'A'||input == 'a'){ 
          return true;
          }
        else if(input == 'h'||input == 'H'){ 
          return false;
        }
}

void PlayerReward(){
switch(LevelNo){
  case 1:{
  cout<<endl<<endl<<Player -> Name()<<" found a map to The Safe Haven!\n\n";
  cout<<"The Abandoned Warehouse\n";
  cout<<"           |\n           V\n";
  cout<<"The Ruined City Streets\n";
  cout<<"           |\n           V\n";
  cout<<"The Infected Hospital\n";
  cout<<"           |\n           V\n";
  cout<<"The Overgrown Forest\n";
  cout<<"           |\n           V\n";
  cout<<"The Desolate Military Base\n";
  cout<<"           |\n           V\n";
  cout<<"The Zombie-Infested Subway\n";
  cout<<"           |\n           V\n";
  cout<<"The Safe Haven\n\n";

  
  cout<<"You will start at the Abandoned Warehouse, and as you progress through the levels, you will make your way through the Ruined City Streets, the Infected Hospital, the Overgrown Forest, the Desolate Military Base, and the Zombie-Infested Subway.\n\n";


  cout<<"Your ultimate goal is to reach the Safe Haven, the final destination where you can find safety and hopefully, a cure for the infection. The journey ahead is perilous, and you must use all of your skills and resources to survive the many dangers that await you.\n\nGood luck on your journey!\n\n\n";
    break;

    }

  case 2:
  cout<<endl<<Player -> Name()<< " Found a Semi-Auto Gun!\n";
  break;

  case 3:
  cout<<endl<<Player -> Name()<< " Found a Sheild!\n";
  break;

  case 4:
  cout<<endl<<Player -> Name()<< " Found a Life Vest!\n";
  break;

  case 5:
  cout<<endl<<Player -> Name()<< " Found a Bow!\n";
  break;

  Default:
  break;
}
}

void GameIntro(){
  cout<<"***************** THE LAST OF US ******************\n\n";
 cout<<"Welcome to the post-apocalyptic world of survival, where the remnants of humanity struggle to survive against the relentless hordes of zombies. As a lone survivor, you must navigate through the dangers and challenges of this harsh and unforgiving world, using only two inputs: [ATTACK] and [HEAL].\n\n\n";
  
cout<<"Each level presents new obstacles and dangers, and you must use your wits and cunning to overcome them. You will encounter zombies, scarce resources, and other challenges along the way, and you must make strategic and resourceful choices to ensure your survival.\n\n\n";

cout<<"As you progress, you will have the chance to unlock special powers that can give you an edge in battle. These powers have a 10% chance of being executed successfully, adding an element of chance and unpredictability to the game.\n\n\n";

cout<<"The journey ahead is perilous, and the road to survival is fraught with danger. But with skill and determination, you may just be able to survive the zombie-infested world and emerge victorious. Good luck!\n\n\n";
}

void PlayerUpdate(){
  switch(LevelNo){
    
    case 1:
    Player -> Set_Health(100);
    Player -> Set_MaxHealth(100);
    Player -> Set_RangedDamage(10);
    Player -> Set_MeleeDamage(5);
    Player -> Set_HealPower(2);
    ZombieCount = 1;
    break;

     case 2:
    Player -> Set_Health(150);
    Player -> Set_MaxHealth(150);
    Player -> Set_RangedDamage(15);
    Player -> Set_MeleeDamage(10);
    Player -> Set_HealPower(4);
    ZombieCount = 2;
    break;

     case 3:
    Player -> Set_Health(200);
    Player -> Set_MaxHealth(200);
    Player -> Set_RangedDamage(20);
    Player -> Set_MeleeDamage(15);
    Player -> Set_HealPower(6);
    ZombieCount = 3;
    break;

     case 4:
    Player -> Set_Health(250);
    Player -> Set_MaxHealth(250);
    Player -> Set_RangedDamage(25);
    Player -> Set_MeleeDamage(20);
    Player -> Set_HealPower(8);
    ZombieCount = 4;
    break;

     case 5:
    Player -> Set_Health(300);
    Player -> Set_MaxHealth(300);
    Player -> Set_RangedDamage(30);
    Player -> Set_MeleeDamage(25);
    Player -> Set_HealPower(10);
    ZombieCount = 5;
    break;

     case 6:
    Player -> Set_Health(400);
    Player -> Set_MaxHealth(400);
    Player -> Set_RangedDamage(50);
    Player -> Set_MeleeDamage(40);
    Player -> Set_HealPower(20);
    ZombieCount = 1;
    break;
  }
}

void Level_1(){
  while (true){
    cout<<"\n\n--------------- ** Level 1 ** --------------------\n\n";
    PlayerUpdate();
    cout<<"A zombie spawned!!\n";
    Zombie = new Enemy(30, 10);
    cout<< "\nZombie Healht: "<<Zombie -> Get_Health()<<endl;
    cout<<endl<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Zombie -> Damage(Player -> Attack(LevelNo, Zombie));
        if(!Zombie -> Is_Alive()){
          ZombieCount --;
          cout<<"\nThe Zombie is Dead!!\n";
          if(ZombieCount != 0){
            delete Zombie;
            cout<<"\nA new zombie spawned!!\n";
            Zombie = new Enemy(30, 10);
            cout<< "\nZombie Healht: "<<Zombie -> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"\nZombie Health: "<<Zombie -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<endl;
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }
      cout<<"\n-----------------------\n";

      if(Zombie -> Is_Alive()){
        cout<<"The Zombie Attacked!!\n\n";
        Player -> Damage(Zombie -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        }
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated the enemy!!\n";
        PlayerReward();
        cout<<"Get Ready for the Next Challenge!!\n";
        delete Zombie;
        LevelNo ++;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n\nLet's try again\n\n";
      }
  }
}

void Level_2(){
  while (true){
    cout<<"\n\n--------------- ** Level 2 ** --------------------\n\n";
    PlayerUpdate();
    cout<<"A zombie spawned!!\n";
    Zombie = new Enemy(40, 15);
    cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
    cout<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Zombie -> Damage(Player -> Attack(LevelNo, Zombie));
        if(!Zombie -> Is_Alive()){
          ZombieCount --;
          cout<<"The Zombie is Dead!!\n";
          if(ZombieCount != 0){
            delete Zombie;
            cout<<"A zombie spawned!!\n";
            Zombie = new Enemy(40, 15);
            cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"Zombie Health: "<<Zombie -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }

       cout<<"\n-----------------------\n";

      if(Zombie -> Is_Alive()){
        cout<<"The Zombie Attacked!!\n\n";
        Player -> Damage(Zombie -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        }
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated all the enemy!!\n";
        PlayerReward();
        cout<<"Get Ready for the Next Challenge!!\n";
        delete Zombie;
        LevelNo++;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n Let's try again\n\n";
      }
  }
}

void Level_3(){
  while (true){
    cout<<"\n\n--------------- ** Level 3 ** --------------------\n\n";
    PlayerUpdate();
    cout<<"A zombie spawned!!\n";
    Zombie = new Enemy(50, 20);
    cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
    cout<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Zombie -> Damage(Player -> Attack(LevelNo, Zombie));
        if(!Zombie -> Is_Alive()){
          ZombieCount --;
          cout<<"The Zombie is Dead!!\n";
          if(ZombieCount != 0){
            delete Zombie;
            cout<<"A zombie spawned!!\n";
            Zombie = new Enemy(50,20);
            cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"Zombie Health: "<<Zombie -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }

       cout<<"\n-----------------------\n";
      
      if(Zombie -> Is_Alive()){
        cout<<"The Zombie Attacked!!\n\n";
        Player -> Damage(Zombie -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        }
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated all the enemy!!\n";
        PlayerReward();
        cout<<"Get Ready for the Next Challenge!!\n";
        delete Zombie;
        LevelNo ++;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n Let's try again\n\n";
      }
  }
}

void Level_4(){
  while (true){
    cout<<"\n\n--------------- ** Level 4 ** --------------------\n\n";
    PlayerUpdate();
    cout<<"A zombie spawned!!\n";
    Zombie = new Enemy(60, 25);
    cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
    cout<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Zombie -> Damage(Player -> Attack(LevelNo, Zombie));
        if(!Zombie -> Is_Alive()){
          ZombieCount --;
          cout<<"The Zombie is Dead!!\n";
          if(ZombieCount != 0){
            delete Zombie;
            cout<<"A zombie spawned!!\n";
            Zombie = new Enemy(60, 25);
            cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"Zombie Health: "<<Zombie -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }

       cout<<"\n-----------------------\n";
      if(Zombie -> Is_Alive()){
        cout<<"The Zombie Attacked!!\n\n";
        Player -> Damage(Zombie -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        }
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated all the enemy!!\n";
        PlayerReward();
        cout<<"Get Ready for the Next Challenge!!\n";
        delete Zombie;
        LevelNo++;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n Let's try again\n\n";
      }
  }
}

void Level_5(){
  while (true){
    cout<<"\n\n--------------- ** Level 5 ** --------------------\n\n";
    PlayerUpdate();
    cout<<"A zombie spawned!!\n";
    Zombie = new Enemy(70, 30);
    cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
    cout<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Zombie -> Damage(Player -> Attack(LevelNo, Zombie));
        if(!Zombie -> Is_Alive()){
          ZombieCount --;
          cout<<"The Zombie is Dead!!\n";
          if(ZombieCount != 0){
            delete Zombie;
            cout<<"A zombie spawned!!\n";
            Zombie = new Enemy(70, 30);
            cout<< "Zombie Healht: "<<Zombie -> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"Zombie Health: "<<Zombie -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }

       cout<<"\n-----------------------\n";
      
      if(Zombie -> Is_Alive()){
        cout<<"The Zombie Attacked!!\n\n";
        Player -> Damage(Zombie -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        }
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated all the enemy!!\n";
        PlayerReward();
        cout<<"Get Ready for the Next Challenge!!\n";
        delete Zombie;
        LevelNo++;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n Let's try again\n\n";
      }
  }
}

void Level_6(){
  while (true){
    cout<<"\n\n--------------- ** THE FINAL CHALLENGE ** --------------------\n\n";
    PlayerUpdate();
    Boss = new class Boss(500, 50, 20);
    cout<< "\nThe Shambler Healht: "<<Boss -> Get_Health()<<endl;
    cout<<Player -> Name()<<" Health: "<<Player -> Get_Health()<<endl;
    while((Player -> Get_Health()) > 0 ){
      if(PlayerInput()){
        Boss -> Damage(Player -> Attack(LevelNo, Boss));
        if(!Boss -> Is_Alive()){
          ZombieCount --;
          cout<<"The Shambler is Dead!!\n";
          if(ZombieCount != 0){
            delete Boss;
            Boss = new class Boss(500, 50, 20);
            cout<< "Shambler Healht: "<<Boss-> Get_Health()<<endl;
          }else{break;}
        }else{
          cout<<"Shambler Health: "<<Boss -> Get_Health()<<endl;
        }
        }
      else{
        Player -> Heal();
        cout<<Player -> Name()<<" has healed\n";
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
      }

       cout<<"\n-----------------------\n";
      
      if (Boss -> is_Attacking()){
          
        if(Boss -> Is_Alive()){
        cout<<"The Shambler Attacked!!\n\n";
        Player -> Damage(Boss -> Get_Damage());
        if(Player -> IsAlive()){
        cout<<Player -> Name()<<" Health : "<<Player -> Get_Health()<<endl;
        }else{
          cout<<Player -> Name()<< " is out of Health\n\n";
          break;
        
          }
        }
      }
      else{
        cout<<"The Shambler is healing!\n\n";
        Boss -> Healing(Player);
      }
    }

      if(Player -> IsAlive() && ZombieCount == 0){
        cout<<"     VICTORY!!!       \n";
        cout<<Player -> Name()<<" has defeated the enemy!!\n";
        delete Boss;
        break;
        
      }else{
        cout<<Player -> Name()<<" has been defeated!!\n Let's try again\n\n";
      }
  }
}

public:

void Player_Spawn(){
   GameIntro();
  Player = new class Player;
}

void GameManager(){
  
  Level_1();
  Level_2();
  Level_3();
  Level_4();
  Level_5();
  Level_6();
}

void GameEnd(){
  cout<<" You saved "<<Player -> Name()<<" form these horrifying dangers\n\n";
  cout<<"Congratulations on reaching the Safe Haven! Your bravery, skill, and determination have brought you through the trials and tribulations of the post-apocalyptic world. You are now the Ultimate Survivor, a legend in the annals of this world. Well done!\n";
  cout<<"Press 'P' to Play again.\nPress 'Q' to Quit.\n\n";
  cin>>input;
  if (input == 'p' || input == 'P'){
    LevelNo = 1;
    GameManager();
  }else{
    cout<<"Thank You For Playing!\n ";
    delete Player;
    cout<<"\n-----------------** END **---------------------\n\n";
  }
}

};



int main() {

  GameSetup Game;
  Game.Player_Spawn();
  Game.GameManager();
  Game.GameEnd();
  
}