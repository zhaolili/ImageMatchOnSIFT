#ifndef _SIFTDLL_H_
#define _SIFTDLL_H_

#define SIFT_API extern "C" _declspec(dllimport)

#define  imgpix unsigned char
#define SIFT_DESC_LEN				128	

//一个极值点信息
typedef struct
{
	int		y;			//关键点空间坐标
	int		x;
	int 	octave;		//所在组数
	int 	scale;		//所在层数
	float	sub_sca;	//亚层数
	//平滑因子
	float   sig_space;	//当前关键点在整个尺度空间内的平滑因子
	float   sig_octave;	//当前关键点在一个组内的平滑因子
	//在原图像分辨率下的坐标
	float   ox;
	float   oy;
	float   orient;		//关键点主方向
	float   descriptor[SIFT_DESC_LEN]; //关键点描述子
}Feature;

//存储一极值点的链表节点
typedef struct feature
{
	Feature *feat;				//存储一个关键点信息
	struct feature *next;	//指向下一个节点
	struct feature *prev;	//指向前一个节点
}FeatureNode;

//存储所有极值点的链表头
typedef struct featureVect
{
	int			to_extr_num;		//所有极值点个数
	FeatureNode *first;				//指向第一个结点
	FeatureNode	*cur_node;			//指向待加入结点的上一个结点
}FeatureVect;


//需要export的
SIFT_API FeatureVect* _sift_main(const char* infile, imgpix	*imgData, int width, int height, float wid, int db_img, float sigma0,\
								 float sigman, float contr_thr, int sift_border_dist, float ill_norm_thresh, int top_oct_reso);
SIFT_API void free_feature_nodes(FeatureVect *featVect);

#endif