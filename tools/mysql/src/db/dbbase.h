#ifndef _DBBASE_H_
#define _DBBASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include <errmsg.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define MAX_LEN_SQL     2048*5
#define TC_DB_DIVIDE_NO 0xffffffff // ���ݿⲻ�ֿ�

#define Record map<string, string>
#define E_OK 0
#define E_ERR -1

//1000~2999 mysql errno

#define DB_CONF_NOT_EXIST				3001
#define DB_INIT_ERR						3002
#define DB_INDEX_ERR					3003
#define DB_NOT_EXIST					3004
#define DB_CONNECTION_ERR				3005
#define DB_FILE_PARSE_ERR				3006
#define DB_FETCH_ROW_ERR				3007



namespace MYDB
{
	/**
	 * ���ݿ����ӽڵ�
	 */
	struct ConnItem
	{
		int m_iStatus; // -2 ��ʼ״̬, -1 ���init ����, 0 ���connect ���� 1 ��ռ��
		int m_iIndex;

		int m_iPort;
		std::string m_strHost;
		std::string m_strUser;
		std::string m_strPasswd;
		std::string m_strDBName;
		MYSQL *m_pLink;
		ConnItem();
	};

	/**
	 * ���ݿ�������Ϣ
	 */
	struct ConfInfo
	{
		int m_iType;
		int m_iStatus;
		int m_iIndex;

		int m_iPort;

		int m_iStart;
		int m_iEnd;

		std::string m_strHost;
		std::string m_strUser;
		std::string m_strPasswd;
		ConfInfo();
	};

	/**
	 * ���ݿ�������
	 */
	class DBConn
	{
	private:
		std::vector<ConfInfo> m_vConfInfo;
		std::vector<ConnItem> m_vConn;

		std::string m_strConfigFile;

		int m_iErrorNo;
		std::string m_strErrorInfo;

	public:
		DBConn();
		~DBConn();

		/**
		 * ��ȡ���ݿ������ļ������������ݿ�
		 * @param config [in] ���ݿ������ļ�
		 * @param strDBType [in] �����ļ��е�tag��ǩ
		 * @return 0�ɹ� ����ʧ��
		 */
		int init(const std::string &config, const std::string &strDBType);

		/**
		 * ��ȡ���ݿ�����
		 * @param dbBit [in] ���ݿ�ֿ�������
		 * @param index [out] ���ݿ�����������
		 * @return 0�ɹ� ����ʧ��
		 */
		MYSQL* getConn(unsigned dbBit, int &index);
		/**
		 * �ͷ����ݿ�����
		 * @param index [in] ���ݿ�����������
		 * @return 0�ɹ� ����ʧ��
		 */
		void releaseConn(int index);
		/**
		 * �������ݿ��
		 * @param index [in] ���ݿ�����������
		 * @return 0�ɹ� ����ʧ��
		 */
		int reconnect(int index, int error_no);

		/**
		 * ִ�в�ѯ����
		 * @param szSql [in] ִ�е�SQL���
		 * @param mysql [out] mysql���
		 * @param result_set [out] ִ�е�mysql�����
		 * @param iDBIndex [in] ���ݿ������ţ����ݿⲻ�ֿ���ΪPUBLISH_DB_DIVIDE_NO
		 * @return 0�ɹ� ����ʧ��
		 */
		int execQuery(const char *szSql, MYSQL *mysql, MYSQL_RES *&result_set,
				int iDBIndex);

		/**
		 * ִ�в����޸�ɾ�����ݿ����
		 * @param szSql [in] ִ�е�SQL���
		 * @param mysql [out] mysql���
		 * @param iDBIndex [in] ���ݿ������ţ����ݿⲻ�ֿ���ΪPUBLISH_DB_DIVIDE_NO
		 * @return 0�ɹ� ����ʧ��
		 */
		int execInsertUpdate(const char *szSql, MYSQL *mysql, int iDBIndex);

		int execInsertUpdate(const char *szSql, MYSQL *mysql, int iDBIndex, int &iAffectRow);

		void ping(void);

		int getErrorNo();
		const char *getErrorInfo();

	private:

		DBConn(const DBConn &);
		DBConn &operator=(const DBConn &);

	private:
		int loadConf(const std::string &strDBType);
		/**
		 * ����ÿ�����ýڵ㴴�����ݿ�����
		 * @return 0�ɹ� ����ʧ��
		 */
		int initConn(void);

		/**
		 * ���ýڵ�����
		 * @param item [in] ���ýڵ�
		 * @return 0�ɹ� ����ʧ��
		 */
		int connect(ConnItem &item);

		/**
		 * Ϊÿ�����ýڵ�Ͽ����ݿ�����
		 * @return 0�ɹ� ����ʧ��
		 */
		void destroyConn();

	};
}

#endif /* _DBBASE_H_ */
