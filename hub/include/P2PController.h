#ifndef P2PCONTROLLER_H
#define P2PCONTROLLER_H
#include <set>

#include <QObject>
#include "SystemCallWrapper.h"
#include "HubController.h"

class P2PConnector : public QObject {
  Q_OBJECT
private:
  QTimer* update_status_timer;

public:

 bool env_connected(const QString& env_id) const {
   return connected_envs.find(env_id) != connected_envs.end();
 }
 bool cont_connected(const QString env_id, const QString& cont_id) const {
   return connected_conts.find(std::make_pair(env_id, cont_id)) != connected_conts.end();
 }
 void startInit();

private:
 std::set< std::pair<QString, QString> > connected_conts; // Connected container. Pair of environment id and container id.
 std::set< QString > connected_envs; // Joined to swarm environment. Id of env is stored
 void join_swarm(const CEnvironment& env);
 void leave_swarm(const QString &hash);
 void check_status(const CEnvironment& env);
 void handshake(const CEnvironment& env, const CHubContainer &cont);
 void check_rh(const CEnvironment& env, const CHubContainer &cont);
private slots:
 void update_status();


};


class P2PController : public QObject
{
  Q_OBJECT

public:
  enum P2P_CONNETION_STATUS{
    CONNECTION_SUCCESS = 0,
    CANT_JOIN_SWARM,
    CANT_CONNECT_CONT,
  };

  P2PController();
  P2PConnector *connector;

  static P2PController& Instance() {
    static P2PController instance;
    return instance;
  }


  void init(){/* need to call constructor */}
  P2P_CONNETION_STATUS is_ready(const CEnvironment&env, const CHubContainer &cont);
  QString p2p_connection_status_to_str(P2P_CONNETION_STATUS status);
  ssh_desktop_launch_error_t is_ready_sdle(const CEnvironment& env, const CHubContainer& cont);


};

#endif // P2PCONTROLLER_H
