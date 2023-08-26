#include "Player.hh"
#include <map>
#include <queue>
#include <cmath>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME SergiCampu


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }
  
  
  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VI;
  typedef vector <bool>VB;
  typedef vector <VB>VVB;
  
    void busca_anterior(map <Pos, Pos> M, int id, Pos posicio, pair<int, int>& ultima_pos) {
        map<Pos, Pos>::iterator it = M.find(posicio);
        if (posicio.i == (it->second).i and posicio.j == (it->second).j) {
            Unit sergi = unit(id);
            if(ultima_pos.first > sergi.pos.i) move(id, Dir(BOTTOM));
            else if(ultima_pos.first < sergi.pos.i) move(id, Dir(TOP));
            else if(ultima_pos.second > sergi.pos.j) move(id, Dir(RIGHT));
            else if(ultima_pos.second < sergi.pos.j) move(id, Dir(LEFT));
        }
        else {
            ultima_pos = make_pair(posicio.i, posicio.j);
            busca_anterior(M, id, it->second, ultima_pos);
        }   
    }
            
    void bfs(int id, int i, int j) {
        VVB vis(70, VB(70, false));
        queue <pair <Pos, Pos > > q;
        Pos p0;
        p0.i = i;
        p0.j = j;
        q.push(make_pair(p0, p0));
        
        map <Pos, Pos> M;
        int x, y, x_ant, y_ant;
        Pos pos_xy;
        Pos pos_xy_ant;
        bool finish = false;
        while (!q.empty() and not finish) {
            x = pos_xy.i = (q.front().first).i;
            y = pos_xy.j = (q.front().first).j; 
            x_ant = pos_xy_ant.i = (q.front().second).i; 
            y_ant = pos_xy_ant.j = (q.front().second).j; 
            
            M.insert(make_pair(pos_xy, pos_xy_ant));
            q.pop();
           
            if ((cell(x, y).type == CITY and city_owner(cell(x, y).city_id) != me()) or (cell(x, y).type == PATH and path_owner(cell(x, y).path_id) != me())) { 
                pair<int, int> ultima_pos = make_pair(x, y);
                busca_anterior(M, id, pos_xy, ultima_pos);
                finish = true;
            }
            
            else if (!vis[x][y]) {
                vis[x][y] = true;
                Pos nuevo;
                if (x != 0 and cell(x - 1, y).type != WALL) {
                    nuevo.i = x - 1;
                    nuevo.j = y;
                    q.push(make_pair(nuevo, pos_xy));
                }
                if (x != 69 and cell(x + 1, y).type != WALL) {
                    nuevo.i = x + 1;
                    nuevo.j = y;
                    q.push(make_pair(nuevo, pos_xy));
                }
                if (y != 0 and cell(x, y - 1).type != WALL) {
                    nuevo.i = x;
                    nuevo.j = y - 1;
                    q.push(make_pair(nuevo, pos_xy));
                }
                if (y != 69 and cell(x, y + 1).type != WALL) {
                    nuevo.i = x;
                    nuevo.j = y + 1;
                    q.push(make_pair(nuevo, pos_xy));
                }
            }
            
        }
  }

            
       
  // Moves all units of the player.
  void move_units() {
	  VI U = my_units(me()); // Get the id's of my units.
      int n = U.size();
      for (int i = 0; i < n; ++i) {
		  // We process the units in order.
          int id = U[i];
		  Unit sergi = unit(id);
          Pos p0 = sergi.pos;
          Pos p1 = p0 + Dir(RIGHT);
          Pos p2 = p0 + Dir(LEFT);
          Pos p3 = p0 + Dir(TOP);
          Pos p4 = p0 + Dir(BOTTOM);
          bool moved = false;

            int x;
            x = cell(p1).unit_id;
            if (not moved and x != -1 and unit(x).player != sergi.player) {
                move(id, Dir(RIGHT));
                moved = true;
            }
            x = cell(p2).unit_id;
            if (not moved and x != -1 and unit(x).player != sergi.player) {
                move(id, Dir(LEFT));
                moved = true;
            }
            x = cell(p3).unit_id;
            if (not moved and x != -1 and unit(x).player != sergi.player) {
                move(id, Dir(TOP));
                moved = true;
            }
            x = cell(p4).unit_id;
            if (not moved and x != -1 and unit(x).player != sergi.player) {
                move(id, Dir(BOTTOM));
                moved = true;
            }
            
            if (not moved) bfs(id, sergi.pos.i, sergi.pos.j);
         
    }
  }
  
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    // If winning, do nothing.
   // if (winning()) return;

    // If nearly out of time, do nothing.
    double st = status(me());
    if (st >= 0.95) return;
    
    move_units();
  }

};
      
/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
