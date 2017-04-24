#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
enum FootballCaseType {
    CASE_Start_RT1 = 100000,// 上半场开始
    CASE_Stop_RT1 = 100001,// 上半场结束
    CASE_Start_RT2 = 100002,// 下半场开始
    CASE_Stop_RT2 = 100003,// 下半场结束
    CASE_Start_OT1 = 100004,// 加时赛上半场开始
    CASE_Stop_OT1 = 100005,// 加时赛上半场结束
    CASE_Start_OT2 = 100006,// 加时赛下半场开始
    CASE_Stop_OT2 = 100007,// 加时赛下半场结束
    CASE_Start_PEN = 100008,// 点球大战开始
    CASE_Stop_PEN = 100009,// 点球大战结束
    CASE_Start_RT1_Team_1 = 100010,// 上半场开始,主队发球
    CASE_Start_RT1_Team_2 = 100011,// 上半场开始,客队发球
    CASE_Start_RT2_Team_1 = 100012,// 下半场开始,主队发球
    
    CASE_Start_RT2_Team_2 = 100013,// 下半场开始,客队发球
    CASE_Start_OT1_Team_1 = 100014,// 加时赛上半场开始,主队发球
    CASE_Start_OT1_Team_2 = 100015,// 加时赛上半场开始,客队发球
    CASE_Start_OT2_Team_1 = 100016,// 加时赛下半场开始,主队发球
    CASE_Start_OT2_Team_2 = 100017,// 加时赛下半场开始,客队发球
    CASE_Start_PEN_Team_1 = 100018,// 点球大战开始,主队发球
    CASE_Start_PEN_Team_2 = 100019,// 点球大战开始,客队发球
    CASE_StopGame = 100020,         // 比赛结束
    CASE_StartOT = 100035,          // 加时赛开始
    CASE_StopOvertime = 100037,     // 加时赛结束
    
    CASE_Missed = 100142,// 点球不中
    CASE_PRC = 100143, // 可能红牌
    CASE_PPEN = 100144,// 可能点球
    CASE_NoRC = 100145,// 无红牌
    CASE_NoPEN = 100146,// 无点球
    CASE_RetakePEN = 100147,// 点球重罚
    CASE_Restart = 100148,// 比赛继续,如伤停之后
    CASE_GameSuspended = 100149,// 比赛因未知原因暂停
    
    CASE_AT1 = 101024,// 主队进攻
    CASE_CR1 = 101025,// 主队角球
    CASE_DAT1 = 101026,// 主队危险进攻
    CASE_DFK1 = 101027,// 主队危险任意球
    CASE_FK1 = 101028,// 主队任意球
    CASE_GOAL1 = 101029,// 主队进球
    CASE_CGOAL1 = 101030,// 主队进球取消
    CASE_PEN1 = 101031, // 主队点球
    CASE_RC1 = 101032,// 主队红牌
    CASE_SH1 = 101033,// 主队射门
    CASE_YC1 = 101034,// 主队黄牌
    
    CASE_SHG1 = 101039,// 主队射正
    CASE_SHB1 = 101040,// 主队射偏
    CASE_SHW1 = 101041,// 主队射中门框
    CASE_F1 = 101042,// 主队犯规
    CASE_O1 = 101043,// 主队越位
    CASE_KO1 = 101044,// 主队开球
    CASE_YRC1 = 101045,// 主队两黄转一红
    CASE_CYC_RC1 = 101046,// 主队两黄转一红取消
    CASE_CRC1 = 101047,// 主队红牌取消
    CASE_CYC1 = 101048,// 主队黄牌取消
    CASE_CPEN1 = 101049,// 主队点球取消
    
    CASE_CCR1 = 101050,// 主队角球取消
    CASE_SAFE1 = 101051,// 主队控球
    CASE_DANGER1 = 101052,// 主队威胁进攻
    CASE_GK1 = 101053,// 主队球门球
    CASE_TI1 = 101054,// 主队界外球
    CASE_SUB1 = 101055,// 主队换人
    CASE_DSH1 = 101056,// 主队威胁射门
    CASE_SAVE1 = 101057,// 主队扑救
    CASE_BLOCKED1 = 101058,// 主队封堵射门
    CASE_RPEN1 = 101059,// 主队重罚点球
    CASE_MPEN1 = 101060,// 主队点球射失
    
    CASE_PPEN1 = 101062,// 主队可能点球
    CASE_BREAKAWAY1 = 101064,// 主队突破
    CASE_CONF_GOAL1 = 101065,// 主队进球确认
    
    CASE_PCR1 = 101066,// 主队可能角球
    CASE_NCR1 = 101067,// 主队无角球
    CASE_AT2 = 102048,// 客队进攻
    CASE_CR2 = 102049,// 客队角球
    CASE_DAT2 = 102050,// 客队危险进攻
    CASE_DFK2 = 102051,// 客队危险任意球
    CASE_FK2 = 102052,// 客队任意球
    CASE_GOAL2 = 102053,// 客队进球
    CASE_CGOAL2 = 102054,// 客队进球取消
    CASE_PEN2 = 102055,// 客队点球
    CASE_RC2 = 102056,// 客队红牌
    CASE_SH2 = 102057,// 客队射门
    CASE_YC2 = 102058,// 客队黄牌
    
    CASE_SHG2 = 102063,// 客队射正
    CASE_SHB2 = 102064,// 客队射偏
    CASE_SHW2 = 102065,// 客队射中门框
    CASE_F2 = 102066,// 客队犯规
    CASE_O2 = 102067,// 客队越位
    CASE_KO2 = 102068,// 客队开球
    CASE_YRC2 = 102069,// 客队两黄转一红
    CASE_CYC_RC2 = 102070,// 客队两黄转一红取消
    CASE_CRC2 = 102071,// 客队红牌取消
    CASE_CYC2 = 102072,// 客队黄牌取消
    CASE_CPEN2 = 102073,// 客队点球取消
    CASE_CCR2 = 102074,// 客队角球取消
    CASE_SAFE2 = 102075,// 客队控球
    CASE_DANGER2 = 102076,// 客队威胁进攻
    CASE_GK2 = 102077,// 客队球门球
    CASE_TI2 = 102078,// 客队界外球
    CASE_SUB2 = 102079,// 客队换人
    CASE_DSH2 = 102080,// 客队威胁射门
    CASE_SAVE2 = 102081,// 客队扑救
    CASE_BLOCKED2 = 102082,// 客队封堵射门
    CASE_RPEN2 = 102083,// 客队点球重罚
    CASE_MPEN2 = 102084,// 客队点球射失
    
    CASE_PPEN2 = 102086,// 客队可能点球
    
    CASE_BREAKAWAY2 = 102088,// 客队突破
    CASE_CONF_GOAL2 = 102089,// 客队进球确认
    CASE_PCR2 = 102090,// 客队可能角球
    CASE_NCR2 = 102091,// 客队无角球
    
   
    
};
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float time);
    
    //常用方法
public:
    void initUI();//UI布局初始化
    
    void startUI();//开赛前的信息
    
    void update_dianqiu(float dt);//点球，角球，球门球实时监测
    void jiaoqiu(int _state);//角球方法，点球，角球，球门球，掷界外球
    
    void kongqiu(int _i);//控球方法 状态：1、控球 2、进攻 3、危险进攻
    void move(Point _point);//球移动到指定的位置
    
    void labUI();//界面labUI的方法
    
    void update_q(float dt);//监测球的位置，当球到达指定位置后，执行球没有移动的时候的阴影动作
    void qshadow(Point _point);//球没有移动的时候的阴影动作
    
    void jinqiu(int _i);//进球的时的进球动画
    void lab_state(int _state,char* _word);//遮罩层上的lab状态显示
    void lab_move(Point _point);
    
    void pai_RY(int _pai);//红牌与黄牌
    
    void injured();//受伤
    
    void alternate();//替补
    
    void overtime(int _i);//加时与半场
    
    void JX_json();//测试json解析
    
    void footballCaseType(int _FootballCaseType);
public:
    void callback1(Node* sender);
    
    void netClick();
    void onHttpRequestCompleted(Node *sender ,void *data);
    void update_cc(float dt);
    //成员变量
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    int cc_state;
    
    cocos2d::ProgressTimer * progress;//控球
    cocos2d::ProgressTimer * progress1;//角球
    cocos2d::Sprite* football;
    cocos2d::Sprite* sprbg;
    cocos2d::Sprite* sp;
    cocos2d::Sprite* sp_wxjg;
    cocos2d::Sprite* sp_kq;
    cocos2d::Sprite*shadow1;
    cocos2d::Sprite*shadow2;
    cocos2d::Sprite*Jqshadow;
    cocos2d::Label*labstr1;
    
    Node*node_lab;//
    Node*node_jinqiu;//进球node
    Node*pai_spr;//红黄牌node
    Node*startUInode;//显示比赛开始时的lab情况
    Sprite*lab_sp;//lab上的矩形
    Label* lab_st;//lab上的进攻状态
    Label* lab;//lab上的球队
    
    char* name_match;
    //赛事的名称
    char* name_teamA;
    //比赛的主场队名
    int teamA_yc;
    //黄牌次数
    int teamA_rc;
    //红牌次数
    int teamA_yw;
    //越位次数
    int teamA_jg;
    //进攻次数
    int teamA_wxjg;
    //危险进攻次数
    int teamA_qq;
    //球权次数
    int teamA_sz;
    //射正球门次数
    int teamA_sw;
    //射偏球门次数
    int teamA_jq;
    //进球次数
    char* name_teamB;
    //比赛的客场队名
    int teamB_yc;
    //黄牌次数
    int teamB_rc;
    //红牌次数
    int teamB_yw;
    //越位次数
    int teamB_jg;
    //进攻次数
    int teamB_wxjg;
    //危险进攻次数
    int teamB_qq;
    //球权次数
    int teamB_sz;
    //射正球门次数
    int teamB_sw;
    //射偏球门次数
    int teamB_jq;
    //进球次数
    
    float lab7_pro_percent;
    //危险进攻比例
    float lab8_pro_percent;
    //进攻比例
    float lab9_pro_percent;
    //球权比例
    float lab_sz_pro_percent;
    //射正球门比例
    float lab_sw_pro_percent;
    //射偏球门比例
private:
    bool state_dq = true;//点球状态判定
    bool state_kongqiu = true;//控球状态判定
    bool state_qmove = true;//球移动状态判定
    bool state_qjiewai = true;//角球状态判定
    
    int percent_jiaoqiu = 0;
    int percent_kongqiu = 0;
    float android_height;
    
};

#endif // __HELLOWORLD_SCENE_H__
