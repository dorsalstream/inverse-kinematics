#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include <map>
#include <string>
using namespace std;

enum ChannelEnum
{
	X_ROTATION,Y_ROTATION,Z_ROTATION,
	X_POSITION,Y_POSITION,Z_POSITION
};

struct Channel;

struct Joint
{
	string            type;        //�ؽ�����
	string            name;       //�ؽ�����
	int               index;      //�ؽ����
	Joint*            parent;     //���ؽ�
	vector<Joint*>    children;   //�ӹؽ�
	double            offset[3];  //���ڵ��ʼλ�ü����λ��
	bool              has_site;   //�Ƿ���ĩ�ڵ�
	double            site[3];    //ĩ��λ��
	vector<Channel*>  channels;   //ͨ����Ϣ
};

struct Channel
{
	Joint*           joint;      //�����ؽ�
	ChannelEnum      type;       //ͨ������
	string           name;       //ͨ������
	int              index;      //ͨ�����

};

class BVH
{
public:
	BVH();
	BVH(const char* bvh_file_name);
	~BVH();
	void Clear();
	void Load(const char* bvh_file_name);
	//�Ƿ���سɹ�
	bool IsLoadSuccess() const { return is_load_success; }
	//��ȡ�ļ�·�����ļ���
	const string& Getfilename() const { return file_name; }
	const string& Getmotionname() const { return motion_name; }
	//��ȡ�ؽڼ�ͨ����Ϣ
	const int GetnumJoint() const { return Joints.size(); }
	 Joint* GetJoint(int no) const { return Joints[no]; }
    double* GetOffsite(int no)const { return (Joints[no])->offset; }
	double* GetSite(int no)const { return (Joints[no])->site; }
	const Joint* GetJoint(const string &j) const {
		map<string, Joint*>::const_iterator i = joint_index.find(j);
		return (i != joint_index.end()) ? (*i).second : NULL;
	}
	const Joint* GetJoint(const char* j) const {
		map<string, Joint*>::const_iterator i = joint_index.find(j);
		return (i != joint_index.end()) ? (*i).second : NULL;
	}
	const int Getnumchannel() const { return channels.size(); }
	const Channel* GetChannel(int no) const { return channels[no]; }
	//��ȡ����������Ϣ
	int    GetNumFrame() const { return num_frame; }
	double GetInterval() const {return interval;   }
	int    GetnumNodes_Line()  const { return  nodes_line.size(); }
	vector<int> Getnodes_Line(int no)   const { return nodes_line[no]; }
	double GetMotion(int f, int c) const { return motion[f*num_channels + c]; }
	//double* GetMotion(int* no);
	//double* GetMotion() { return motion; 
	//�޸�������Ϣ
	void   SetNumframe(int n)    { num_frame = n; }
	void   ResizeMotion(int m, int n) { motion=new double[m*n]; }
	void   SetMotion(int f, int c, double v)  { motion[f*num_channels + c] = v; }
	//д��bvh�ļ�
	friend void  WriteBVH(const char *bvh_file_name,const BVH &A);
/*	void   WriteBrace(FILE *file);
	void   WriteJoint(FILE *file, Joint* joint);
	void   Writeframe(FILE *file, int num_frame, double intervel);
	void   WriteMotion(FILE *file, double* motion);*/
private:
	bool            is_load_success;     //�Ƿ���سɹ�
	string          motion_name;         //�ļ���
	string          file_name;           //�ļ�·����
	int             num_channels;        //ͨ������
	vector<Channel*> channels;           //����ͨ����Ϣ
	vector<Joint*>   Joints;             //���йؽ���Ϣ
	map<string, Joint*>   joint_index;   //�ؽ����ֶ�Ӧ�ùؽ����ݽṹ
	vector<vector<int> >  nodes_line;    //������
	int             num_frame;           //֡��
	double          interval;            //Ƶ��
	double*         motion;              //�˶�����
	//double*        coordinate          //ÿ֡ÿ���ؽ�λ������
};


#endif