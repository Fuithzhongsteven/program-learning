#ifndef __HANDLERTHREAD_H_
#define __HANDLERTHREAD_H_

extern struct HandlerTask_t;
extern struct HandlerMsg_t;
extern struct ThreadHandler_t;

typedef struct ThreadHandler_t ThreadHandler_t;

typedef struct HandlerTask_t HandlerTask_t;
typedef int (*HandleTask)(HandlerTask_t *thisTask,void *param) TaskHandler_F;

typedef struct HandlerMsg_t HandlerMsg_t;
typedef int (*HandleMsg)(HandlerMsg_t *thisMsg,int type, int arg1, int arg2, void *param) MsgHandler_F;

/*创建handler thread*/
extern ThreadHandler_t *threadHandlerCreate(const char * name);
/*释放handler thread*/
extern int threadHandlerFree(ThreadHandler_t *handler);
/*向thread handler中添加任务*/
extern int addTask(HandlerTask_t *task, unsigned long time);
extern int removeTask(HandlerTask_t *task);
extern int addTaskWithArgs(HandlerTask_t *task, void* param, unsigned long time);
extern int removeTaskWithArgs(HandlerTask_t *task, void* param,);

extern int addMsg(HandlerMsg_t *msg, unsigned long time);
extern int addMsgWithArgs(int type, int arg1, int arg2, void *param, MsgHandler_F handler, unsigned long time);
extern int removeMsg(HandlerMsg_t *msg);
extern int removeMsgWithType(int type);

//msg and task utils
extern HandlerMsg_t* createMsg(int type, int arg1, int arg2, void *param, unsigned long time, MsgHandler_F handler);
extern void destoryMsg(HandlerMsg_t*msg);
extern HandlerTask_t* createTask(TaskHandler_F, void *param, unsigned long time);



#endif






