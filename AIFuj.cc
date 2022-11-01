#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Fuji


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  typedef vector<int> VI;

  bool winning() {
		for (int pl = 0; pl < nb_players(); ++pl)
      if (pl != me() and total_score(me()) <= total_score(pl))
        return false;
    return true;
  }


  bool jugador_enemic(Pos p,int id,Pos& p1) {
    bool atacar = false;
    for (int d = 0;d < 4 and not atacar;++d) {
      Pos p1 = p+Dir(d);
      if (cell(p1).unit_id != -1) {
        Unit u1 = unit(cell(p1).unit_id);
				if (u1.player != me()) {
          atacar = true;
        }
      }
    }
    return atacar;
  }

  void cami(int id) {

    Unit u = unit(id);
    Pos p = u.pos;
    Cell c0 = cell(p);
    Pos dest;
    if (c0.type == PATH) {
      bool atacar = false;
      int idpath = c0.path_id;
      for (int d = 0;d < 4 and not atacar;++d) {
        Pos p1 = p+Dir(d);
        if (cell(p1).unit_id != -1) {
          Unit u1 = unit(cell(p1).unit_id);
					if (u1.player != me()) {
            move(id, Dir(d));
            atacar = true;
          }
        }
      }
      if (not atacar) {
          queue<Pos> q;
          vector<vector<int> > dist(70,vector<int>(70,-1));
          vector<vector<Pos> > prev(70,vector<Pos>(70));
          dist[p.i][p.j] = 0;
          q.push(p);
          bool found = false;
          while (not q.empty() and not found) {
            Pos p1 = q.front();
            q.pop();
            for (int d = 0;d < 4;++d) {
              Pos p2 = p1+Dir(d);
              Cell c = cell(p2);
              if (pos_ok(p2) and c.virus == 0 and dist[p2.i][p2.j] == -1 and c.type != WALL and c.unit_id == -1) {
                dist[p2.i][p2.j] = dist[p1.i][p1.j]+1;
                prev[p2.i][p2.j] = p1;
                q.push(p2);
                if (not u.immune and c.mask and not u.mask) {
                  found = true;
                  dest = p2;
                }
                else if (c.type == CITY) {
                  int id = c.city_id;
                  if (city_owner(id) != me()) {
                    found = true;
                    dest = p2;
                  }
                }
                else if (c.type == PATH) {
                  int id = c.path_id;
                  if (path_owner(id) != me()) {
                    found = true;
                    dest = p2;
                  }
                }
              } 
            }
          if (found) {
            stack<Pos> S;
            Pos actual = dest;
            while (actual !=p) {
              S.push(actual);
              actual = prev[actual.i][actual.j];
            }
            S.push(actual);

            vector<Pos> resultat;
            while (not S.empty()) {
              resultat.push_back(S.top());
              S.pop();
            }
            Pos p3 = resultat[0];
            Pos p4 = resultat[1];
            if ((p4.i - p3.i) == 0) {
              if ((p4.j - p3.j) == 1) move(id,RIGHT);
              else if ((p4.j - p3.j) == -1) move(id,LEFT);
            }
            else if ((p4.j - p3.j) == 0) {
              if ((p4.i - p3.i) == 1) move(id,BOTTOM);
              else if ((p4.i - p3.i) == -1) move(id,TOP);
            }
          }
        }
      }
    }
    else if (c0.type == CITY) {
        bool atacar = false;
        for (int d = 0;d < 4 and not atacar;++d) {
          Pos p1 = p+Dir(d);
          if (cell(p1).unit_id != -1) {
            Unit u1 = unit(cell(p1).unit_id);
						if (u1.player != me()) {
              move(id, Dir(d));
              atacar = true;
            }
          }
        }
        if (not atacar) {
          queue<Pos> q;
          vector<vector<int> > dist(70,vector<int>(70,-1));
          vector<vector<Pos> > prev(70,vector<Pos>(70));
          dist[p.i][p.j] = 0;
          q.push(p);
          bool found = false;
          while (not q.empty() and not found) {
            Pos p1 = q.front();
            q.pop();
            for (int d = 0;d < 4;++d) {
              Pos p2 = p1+Dir(d);
              Cell c = cell(p2);
              if (pos_ok(p2) and c.virus == 0 and dist[p2.i][p2.j] == -1 and c.type != WALL and c.unit_id == -1) {
                  dist[p2.i][p2.j] = dist[p1.i][p1.j]+1;
                  prev[p2.i][p2.j] = p1;
                  q.push(p2);
                  if (not u.immune and c.mask and not u.mask) {
                    found = true;
                    dest = p2;
                  }
                  else if (c.type == CITY) {
                    int id = c.city_id;
                    if (city_owner(id) != me()) {
                      found = true;
                      dest = p2;
                    }
                  }
                  else if (c.type == PATH) {
                    int id = c.path_id;
                    if (path_owner(id) != me()) {
                      found = true;
                      dest = p2;
                    }
                  }
              } 
            } 
            if (found) {
            stack<Pos> S;
            Pos actual = dest;
            while (actual !=p) {
              S.push(actual);
              actual = prev[actual.i][actual.j];
            }
            S.push(actual);

            vector<Pos> resultat;
            while (not S.empty()) {
              resultat.push_back(S.top());
              S.pop();
            }
            Pos p3 = resultat[0];
            Pos p4 = resultat[1];
            if ((p4.i - p3.i) == 0) {
              if ((p4.j - p3.j) == 1) move(id,RIGHT);
              else if ((p4.j - p3.j) == -1) move(id,LEFT);
            }
            else if ((p4.j - p3.j) == 0) {
              if ((p4.i - p3.i) == 1) move(id,BOTTOM);
              else if ((p4.i - p3.i) == -1) move(id,TOP);
            }
          }
        }
      }
    }
    else if (u.damage == 0 and c0.type != CITY and c0.type != PATH) {
      queue<Pos> q;
      vector<vector<int> > dist(70,vector<int>(70,-1));
      vector<vector<Pos> > prev(70,vector<Pos>(70));
      dist[p.i][p.j] = 0;
      q.push(p);
      bool found = false;
      while (not q.empty() and not found) {
          Pos p1 = q.front();
          q.pop();
          for (int d = 0;d < 4;++d) {
            Pos p2 = p1+Dir(d);
            Cell c = cell(p2);
            if (pos_ok(p2) and c.virus == 0 and dist[p2.i][p2.j] == -1 and c.type != WALL) {
              dist[p2.i][p2.j] = dist[p1.i][p1.j]+1;
              prev[p2.i][p2.j] = p1;
              q.push(p2);
              if (not u.immune and c.mask and not u.mask) {
                  found = true;
                  dest = p2;
              }
              else if (c.type == CITY) {
                int id=c.city_id;
                if (city_owner(id) != me()) {
                  found = true;
                  dest = p2;
                }
              }
              else if (c.type == PATH) {
                int id=c.path_id;
                if (path_owner(id) != me()) {
                  found = true;
                  dest = p2;
                }
              }
            }
          }
      }
    
      if (found) {
        stack<Pos> S;
        Pos actual = dest;
        while (actual !=p) {
          S.push(actual);
          actual = prev[actual.i][actual.j];
        }
        S.push(actual);

        vector<Pos> resultat;
        while (not S.empty()) {
         resultat.push_back(S.top());
         S.pop();
        }
        Pos p3 = resultat[0];
        Pos p4 = resultat[1];
        if ((p4.i - p3.i) == 0) {
          if ((p4.j - p3.j) == 1) move(id,RIGHT);
          else if ((p4.j - p3.j) == -1) move(id,LEFT);
        }
        else if ((p4.j - p3.j) == 0) {
          if ((p4.i - p3.i) == 1) move(id,BOTTOM);
          else if ((p4.i - p3.i) == -1) move(id,TOP);
        }
      }
      /*else move(id, Dir(random(0, DIR_SIZE - 1)));*/
    }
    
    else if (u.damage > 0) {
      bool atacar = false;
      for (int d = 0;d < 4 and not atacar;++d) {
        Pos p1 = p+Dir(d);
        if (cell(p1).unit_id != -1 and pos_ok(p1)) {
          Unit u1 = unit(cell(p1).unit_id);
				  if (u1.player != me()) {
            move(id,Dir(d));
            atacar = true;
          }
        }
      }
      if (round() >= 5 and not atacar) {
        queue<Pos> q;
        vector<vector<int> > dist(70,vector<int>(70,-1));
        vector<vector<Pos> > prev(70,vector<Pos>(70));
        dist[p.i][p.j] = 0;
        q.push(p);
        bool found = false;
        while (not q.empty() and not found) {
          Pos p1 = q.front();
          q.pop();
          for (int d = 0;d < 4;++d) {
            Pos p2 = p1+Dir(d);
            Cell c = cell(p2);
            if (pos_ok(p2) and dist[p2.i][p2.j] == -1 and c.type != WALL) {
              dist[p2.i][p2.j] = dist[p1.i][p1.j]+1;
              prev[p2.i][p2.j] = p1;
              q.push(p2);
              if (c.mask and not u.mask) {
                  found = true;
                  dest = p2;
              }
            }
          }
        }
        if (found) {
          stack<Pos> S;
          Pos actual = dest;
          while (actual !=p) {
            S.push(actual);
            actual = prev[actual.i][actual.j];
          }
          S.push(actual);

          vector<Pos> res;
          while (not S.empty()) {
            res.push_back(S.top());
            S.pop();
          }   
          int n = res.size();
          Pos p3 = res[0];
          Pos p4 = res[1];
          if ((p4.i - p3.i) == 0) {
            if ((p4.j - p3.j) == -1) move(id,LEFT);
            else if ((p4.j - p3.j) == 1) move(id,RIGHT);
          }
          else if ((p4.j - p3.j) == 0) {
            if ((p4.i - p3.i) == -1) move(id,TOP);
            else if ((p4.i - p3.i) == 1) move(id,BOTTOM);
          }
        }
        else {
          queue<Pos> q;
          vector<vector<int> > dist(70,vector<int>(70,-1));
          vector<vector<Pos> > prev(70,vector<Pos>(70));
          dist[p.i][p.j] = 0;
          q.push(p);
          bool found = false;
          while (not q.empty() and not found) {
            Pos p1 = q.front();
            q.pop();
            for (int d = 0;d < 4;++d) {
              Pos p2 = p1+Dir(d);
              Cell c = cell(p2);
              if (pos_ok(p2) and dist[p2.i][p2.j] == -1 and c.type != WALL) {
                dist[p2.i][p2.j] = dist[p1.i][p1.j]+1;
                prev[p2.i][p2.j] = p1;
                q.push(p2);
                if (c.type == CITY or c.type == PATH) {
                  found = true;
                  dest = p2;
                }
              }
            }
          }
          if (found) {
            stack<Pos> S;
            Pos actual = dest;
            while (actual !=p) {
              S.push(actual);
              actual = prev[actual.i][actual.j];
            }
            S.push(actual);
            vector<Pos> resultat;
            while (not S.empty()) {
              resultat.push_back(S.top());
              S.pop();
            }
            Pos p3 = resultat[0];
            Pos p4 = resultat[1];
            if ((p4.i - p3.i) == 0) {
              if ((p4.j - p3.j) == 1) move(id,RIGHT);
              else if ((p4.j - p3.j) == -1) move(id,LEFT);
            }
            else if ((p4.j - p3.j) == 0) {
              if ((p4.i - p3.i) == 1) move(id,BOTTOM);
              else if ((p4.i - p3.i) == -1) move(id,TOP);
            }
          }
          else move(id,Dir(random(0,4)));
        }
      }
    }
  }   

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    VI U = my_units(me()); // Get the id's of my units.
	  int n = U.size();
	  for (int i = 0; i < n; ++i) {
		  int id = U[i];
          cami(id);
		}
  }
};



/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);