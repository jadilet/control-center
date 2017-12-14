#ifndef P2PCONTROLLER_H
#define P2PCONTROLLER_H
#include <set>

#include <QObject>
#include "SystemCallWrapper.h"
#include "HubController.h"

class SwarmConnector : public QObject{
Q_OBJECT
private:
  QString swarm_hash, swarm_key;

public:
  SwarmConnector(QString swarm_hash, QString swarm_key);
  ~SwarmConnector();

public slots:
  void join_to_swarm_begin();
signals:
  void join_to_swarm_finished();
  void successfully_joined_swarm(QString);
};

class HandshakeSender : public QObject {
Q_OBJECT
private:
  std::vector<CEnvironment> m_envs;

public:
  HandshakeSender(const std::vector <CEnvironment> envs);
  ~HandshakeSender();

  void try_to_handshake(const CEnvironment &env, const CHubContainer &cont);
  void send_handshakes();

signals:
  void sent_handshakes_succsessfully();
  void handshake_success(QString, QString);
  void handshake_failure(QString, QString);
};

class P2PController : public QObject
{
  Q_OBJECT
private:
  QTimer* m_handshake_timer;
  QTimer* m_join_to_swarm_timer;

public:
 P2PController();
 ~P2PController();

 bool join_swarm_success(QString swarm_hash);
 bool handshake_success(QString env_id, QString cont_id);

 void join_swarm(const CEnvironment &env);
 void leave_swarm(const CEnvironment &env);
 void try_to_handshake(const CEnvironment &env, const CHubContainer &cont);
 void send_handshake(const CEnvironment &env, const CHubContainer &cont);
 void check_handshakes(const std::vector<CEnvironment>& envs);

 std::vector<CEnvironment> get_joined_envs();

 std::set<QString> envs_joined_swarm_hash;
 std::set<std::pair<QString, QString>> successfull_handshakes; // stores env_id and cont_id

 static P2PController& Instance() {
   static P2PController instance;
   return instance;
 }
 void init(){/* need to call constructor */}

public slots:
 void joined_swarm(QString hash);
 void handshaked(QString env_id, QString cont_id);
 void handshake_failed(QString env_id, QString cont_id);

signals:

public slots:
  void update_handshake_status();
  void update_join_swarm_status();
  void p2p_restart();
};

#endif // P2PCONTROLLER_H