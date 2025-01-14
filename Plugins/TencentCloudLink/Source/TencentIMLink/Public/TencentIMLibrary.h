﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "TencentDataType.h"

#include "V2TIMBuffer.h"
#include "V2TIMConversationManager.h"
#include "V2TIMDefine.h"
#include "V2TIMManager.h"
#include "V2TIMMessage.h"
#include "V2TIMMessageManager.h"
#include "V2TIMGroupManager.h"
#include "V2TIMFriendshipManager.h"
#include "V2TIMSignaling.h"
#include "V2TIMSignalingManager.h"

#include "TencentIMMacros.h"

#include "TencentIMLibrary.generated.h"

/**
 * 
 */
#if PLATFORM_ANDROID
#include "Runtime/Launch/Public/Android/AndroidJNI.h"
#include "Runtime/Core/Public/Android/AndroidJavaEnv.h"
#include "Runtime/ApplicationCore/Public/Android/AndroidApplication.h"
#else
//#include "GenerateTestUserSig.h"
#endif

UCLASS()
class TENCENTIMLINK_API UTencentIMLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "TencentIMLink|Init")
	static ELoginStatus GetLoginStatus();

	UFUNCTION(BlueprintPure, Category = "TencentIMLink|Init")
	static FString GetSDKVersion();

	UFUNCTION(BlueprintPure, Category = "TencentIMLink|Init")
	static int64 GetServerTime();

	/**
	 *
	*/
	// UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Init")
	// static void InitAccounts(const FString& InUserId, const FString& InIMUserSigId);


	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Log")
	static void LogIn(const FString& InUserId, const FString& InIMUserSigId,FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Log")
	static void LogOut(FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintPure, Category = "TencentIMLink|Init")
	static FString GetLoginUser();

	/*
	 * 3.1 设置基本消息（文本消息和自定义消息）的事件监听器
	 */


	// static void AddSimpleMsgListener(V2TIMSimpleMsgListener* listener);
	//
	// static void RemoveSimpleMsgListener(V2TIMSimpleMsgListener* listener);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Log")
	static FString SendC2CTextMessage(FString text, FString userId, FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate,
	                                  FIMProgressCallback OnProgressDelegate);

	/*
	 * 3.4 发送单聊自定义（信令）消息（最大支持 8KB）
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Log")
	static FString SendC2CCustomMessage(const FBuffer& customData, const FString& userID, FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate,
											  FIMProgressCallback OnProgressDelegate) ;

	/*
	 * 3.5 发送群聊普通文本消息（最大支持 8KB）
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink")
	static FString SendGroupTextMessage(const FString& text, const FString& groupID, EIMMessagePriority priority, FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate,
												FIMProgressCallback OnProgressDelegate);

	/**
	 *	3.6 发送群聊自定义（信令）消息（最大支持 8KB）
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink")
	static FString SendGroupCustomMessage(const FBuffer& customData, const FString& groupID, EIMMessagePriority priority,FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate,
	   FIMProgressCallback OnProgressDelegate);


	///-----------------------------------------------------------------------------
	/*
	 *	groupType	群类型，我们为您预定义好了几种常用的群类型，您也可以在控制台定义自己需要的群类型：
		"Work" ：工作群，成员上限 200 人，不支持由用户主动加入，需要他人邀请入群，适合用于类似微信中随意组建的工作群（对应老版本的 Private 群）。
		"Public" ：公开群，成员上限 2000 人，任何人都可以申请加群，但加群需群主或管理员审批，适合用于类似 QQ 中由群主管理的兴趣群。
		"Meeting" ：会议群，成员上限 6000 人，任何人都可以自由进出，且加群无需被审批，适合用于视频会议和在线培训等场景（对应老版本的 ChatRoom 群）。
		"Community" ：社群，成员上限 100000 人，任何人都可以自由进出，且加群无需被审批，适合用于知识分享和游戏交流等超大社区群聊场景。5.8 版本开始支持，需要您购买旗舰版套餐。
		"AVChatRoom" ：直播群，人数无上限，任何人都可以自由进出，消息吞吐量大，适合用作直播场景中的高并发弹幕聊天室。
		groupID	自定义群组 ID，可以传空字符串，此时系统会自动分配 groupID，并通过 callback 返回。 "Community" 类型自定义群组 ID 必须以 "@TGS#_" 作为前缀。
		groupName	群名称，不能为空字符串。
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Group")
	static void CreateGroup(const FString& groupType, const FString& groupID, const FString& groupName, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Group")
	static void JoinGroup(const FString& groupID, const FString& message, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Group")
	static void QuitGroup(const FString& groupID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Group")
	static void DismissGroup(const FString& groupID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	
	//--------------------------------------------
	//User func
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|User")
	static void GetUsersInfo(const TArray<FString>& userIDList, FIMUserFullInfoCallback UserInfoDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|User")
	static void SetSelfInfo(const FTIMUserFullInfo& Info, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	//------------------------------
	//AddAdvancedMsgListener

	/*
	 * 2.1 创建文本消息
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateTextMessage(const FString& text);

	/*
	 * 2.2 创建文本消息，并且可以附带 @ 提醒功能
	 * 提醒消息仅适用于在群组中发送的消息
	 * 参数：
	 * atUserList	需要 @ 的用户列表，如果需要 @ALL，请传入 kImSDK_MesssageAtALL 常量字符串。 举个例子，假设该条文本消息希望@提醒 denny 和 lucy 两个用户，
	 * 同时又希望 @所有人，atUserList 传 {"denny","lucy",kImSDK_MesssageAtALL}
	 *
	 * atUserList 使用注意事项
	 * 默认情况下，最多支持 @ 30个用户，超过限制后，消息会发送失败。
	 * atUserList 的总数不能超过默认最大数，包括 @ALL。
	 * 直播群（AVChatRoom）不支持发送 @ 消息。
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateTextAtMessage(const FString& text, const TArray<FString>& atUserList);


	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|Message")
	static FTIMMessage CreateCustomMessage(const FBuffer& data);

	
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|Message")
	static FTIMMessage CreateCustomMessage_MultiPara(const FBuffer& data, const FString& description, const FString& extension);


	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateImageMessage(const FString& imagePath);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateSoundMessage(const FString& soundPath, int32 duration);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateVideoMessage(const FString& videoFilePath, const FString& type, int32 duration, const FString& snapshotPath);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateFileMessage(const FString& filePath, const FString& fileName);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateLocationMessage(const FString& desc, double longitude, double latitude);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|Message")
	static FTIMMessage CreateFaceMessage(int32 index, const FBuffer& data);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateMergerMessage(const TArray<FTIMMessage>& messageList, const FString& title, const TArray<FString>& abstractList, const FString& compatibleText);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FTIMMessage CreateForwardMessage(const FTIMMessage& message);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|Message")
	static FString SendMessage(const FTIMMessage& message, const FString& receiver, const FString& groupID, EIMMessagePriority priority,
	bool onlineUserOnly, const FTIMOfflinePushInfo& offlinePushInfo, FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate,
				   FIMProgressCallback OnProgressDelegate);


	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void SetC2CReceiveMessageOpt(const TArray<FString>& userIDList, ETIMReceiveMessageOpt opt, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void GetC2CReceiveMessageOpt(const TArray<FString>& userIDList, FMessage_ArrayCallbackTextDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void SetGroupReceiveMessageOpt(const FString& groupID, ETIMReceiveMessageOpt opt, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void GetHistoryMessageList(const FTIMMessageListGetOption& option, FIMGroupMessageInfoCallback OnSuccess, FIMFailureCallback OnFailure);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void RevokeMessage(const FTIMMessage& message, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void MarkC2CMessageAsRead(const FString& userID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void MarkGroupMessageAsRead(const FString& groupID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void MarkAllMessageAsRead(FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void DeleteMessages(const TArray<FTIMMessage>& messages, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void ClearC2CHistoryMessage(const FString& userID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void ClearGroupHistoryMessage(const FString& groupID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FString InsertGroupMessageToLocalStorage(FTIMMessage& message, const FString& groupID, const FString& sender, FIMMessageInfoCallback OnSuccessDelegate,
	                                                FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static FString InsertC2CMessageToLocalStorage(FTIMMessage& message, const FString& userID, const FString& sender, FIMMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void FindMessages(const TArray<FString>& messageIDList, FIMGroupMessageInfoCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|Advanced|IMMessageManager")
	static void SearchLocalMessages(const FTIMMessageSearchParam& searchParam, FMessageSearchResultCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	1.1 创建自定义群组（高级版本：可以指定初始的群成员）

	参数
	info	自定义群组信息，可以设置 groupID | groupType | groupName | notification | introduction | faceURL 字段
	memberList	指定初始的群成员（直播群 AVChatRoom 不支持指定初始群成员，memberList 请传 null）
	注意
	其他限制请参考 V2TIMManager.createGroup 注释 
	*/
	// todo :::::name is same ,so i changed it
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void CreateGroupByMemBer(const FTIMGroupInfo& info, const TArray<FTIMCreateGroupMemberInfo>& memberList, FIMCallbackTextDelegate OnSuccessCallback, FIMFailureCallback OnFailureDelegate);


	/* 
	1.2 获取当前用户已经加入的群列表

	注意
	直播群(AVChatRoom) 不支持该 API。
	该接口有频限检测，SDK 限制调用频率为1 秒 10 次，超过限制后会报 ERR_SDK_COMM_API_CALL_FREQUENCY_LIMIT （7008）错误
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void GetJoinedGroupList(FIMGroupInfoArrayCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	static TArray<FTIMGroupInfo> ToGroupInfoArray(const V2TIMGroupInfoVector& GroupInfoVector);
	static V2TIMGroupInfoVector ToTIMGroupInfoVector(const TArray<FTIMGroupInfo>& GroupInfo);


	//
	// 	/* 
	// 	2.3 修改群资料 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void SetGroupInfo(const FTIMGroupInfo& info, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	// 	/* 
	// 	2.8 获取指定群在线人数
	//
	// 	注意
	// 	请注意：
	// 	目前只支持：直播群（AVChatRoom）。
	// 	该接口有频限检测，SDK 限制调用频率为60秒1次 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void GetGroupOnlineMemberCount(const FString& groupID, FGroupMemCountCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	//
	// 	/* 
	// 	3.1 获取群成员列表
	//
	// 	参数
	// 	filter	指定群成员类型
	// 	V2TIMGroupMemberFullInfo.V2TIM_GROUP_MEMBER_FILTER_ALL：所有类型
	// 	V2TIMGroupMemberFullInfo.V2TIM_GROUP_MEMBER_FILTER_OWNER：群主
	// 	V2TIMGroupMemberFullInfo.V2TIM_GROUP_MEMBER_FILTER_ADMIN：群管理员
	// 	V2TIMGroupMemberFullInfo.V2TIM_GROUP_MEMBER_FILTER_COMMON：普通群成员
	// 	nextSeq	分页拉取标志，第一次拉取填0，回调成功如果 nextSeq 不为零，需要分页，传入再次拉取，直至为0。
	// 	注意
	// 	普通群（工作群、会议群、公开群、社群）的限制：
	// 	filter 只能设置为 V2TIMGroupMemberFullInfo 定义的数值，SDK 会返回指定角色的成员。 直播群（AVChatRoom）的限制：
	// 	如果设置 filter 为 SDK 定义的数值，SDK 返回全部成员。返回的人数规则为：旗舰版支持拉取最近入群群成员最多 1000 人，新进来的成员排在前面（6.3 及以上版本支持，需要先在 控制台 开启开关；非旗舰版支持拉取最近入群群成员最多 31 人，新进来的成员排在前面。
	// 	如果设置 filter 为群成员自定义标记，旗舰版支持拉取指定标记的成员列表。标记群成员的设置请参考 markGroupMemberList API。
	// 	程序重启后，请重新加入群组，否则拉取群成员会报 10007 错误码。
	// 	群成员资料信息仅支持 userID | nickName | faceURL | role 字段。 
	// 	*/


	//todo finish
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void GetGroupMemberList(const FString& groupID, int64 filter, const FString& nextSeq, FTIMGroupMemberInfoResultCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	//
	// 	/* 
	// 	3.2 获取指定的群成员资料 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void GetGroupMembersInfo(const FString& groupID, const TArray<FString>& memberList, FGroupMemFullInfosCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	static V2TIMGroupMemberFullInfoVector ToGroupMemberFullInfoVector(const TArray<FTIMGroupMemberFullInfo>& GPFullInfos);

	static TArray<FTIMGroupMemberFullInfo> ToTIMGroupMemberFullInfoArray(const V2TIMGroupMemberFullInfoVector& GPFullInfos);


	/*
	3.5 禁言（只有管理员或群主能够调用）

	参数
	seconds	禁言时间长度，单位秒，表示调用该接口成功后多少秒内不允许被禁言用户再发言。
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void MuteGroupMember(const FString& groupID, const FString& userID, int32 seconds, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	//
	// 	/* 	
	// 	3.6 邀请他人入群
	//
	// 	注意
	// 	请注意不同类型的群有如下限制：
	// 	工作群（Work）：群里的任何人都可以邀请其他人进群。
	// 	会议群（Meeting）和公开群（Public）：只有通过rest api 使用 App 管理员身份才可以邀请其他人进群。
	// 	直播群（AVChatRoom）：不支持此功能。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void InviteUserToGroup(const FString& groupID, const TArray<FString>& userList, FGroupIniteUserCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	static TArray<FTIMGroupMemberOperationResult> ToGPMemOpArray(const V2TIMGroupMemberOperationResultVector& GPMemOPVector);


	//
	// 	/* 
	// 	4.1 获取加群申请列表 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void GetGroupApplicationList(FGroupAppRstCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	
	static FTIMGroupApplicationResult ToGroupAppResArray(const V2TIMGroupApplicationResult& GroupApplicationResult);
	static V2TIMGroupApplicationResult ToTIMGroupAppRes(const FTIMGroupApplicationResult& GroupApplicationResult);
	static FTIMGroupApplication ToGroupApp(const V2TIMGroupApplication& TIMGroupApplication);
	static V2TIMGroupApplication ToTIMGroupApp(const FTIMGroupApplication& TIMGroupApplication);

	
	/* 4.2 同意某一条加群申请*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void AcceptGroupApplication(const FTIMGroupApplication& application, const FString& reason, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	/* 	4.3 拒绝某一条加群申请 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void RefuseGroupApplication(const FTIMGroupApplication& application, const FString& reason, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	/* 4.4 标记申请列表为已读 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMGroupManager")
	static void SetGroupApplicationRead(FIMCallbackDelegate OnSuccessDelegate,FIMFailureCallback OnFailureDelegate);



	
	/* 
	1.1 添加关系链监听器 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void AddFriendListener(FFriendAPPArrayAddedCallback FriendAppArrayAddedCallback,FFriendAPPArrayDeletedCallback APPDeleteDelegate,FIMCallbackDelegate FriendApplicationListRead,
		FFriendListAddedCallback ListAddedCallback,FFriendListDeletedCallback FriendListDeletedCallback,FBlackListAddedCallback BlackListAddedCallback,
		FBlackListDeletedCallback BlackListDeletedCallback,FFriendInfoChangedCallback FriendInfoChangedCallback);
	static V2TIMFriendshipListener* Friendlistener;
	// /* 
	// 1.2 移除关系链监听器 
	// */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void RemoveFriendListener(FFriendAPPArrayAddedCallback FriendAppArrayAddedCallback,FFriendAPPArrayDeletedCallback APPDeleteDelegate,FIMCallbackDelegate FriendApplicationListRead,
		FFriendListAddedCallback ListAddedCallback,FFriendListDeletedCallback FriendListDeletedCallback,FBlackListAddedCallback BlackListAddedCallback,
		FBlackListDeletedCallback BlackListDeletedCallback,FFriendInfoChangedCallback FriendInfoChangedCallback);


	//
	// /* 
	// 2.1 获取好友列表 
	// */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void GetFriendList(FTIMFriendInfoVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	

	//
	// /* 
	// 1.1 添加会话监听器 
	// */
	// UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	// static void AddConversationListener(V2TIMConversationListener* listener);
	//
	//
	// /* 
	// 1.2 移除会话监听器 
	// */
	// UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	// static void RemoveConversationListener(V2TIMConversationListener* listener);
	//


















	


















	
	
	// 	todo shijia
	// 	/* 
	// 	邀请某个人
	//
	// 	参数
	// 	invitee	被邀请人用户 ID
	// 	data	自定义数据
	// 	onlineUserOnly	是否只有在线用户才能收到邀请，如果设置为 true，只有在线用户才能收到， 并且 invite 操作也不会产生历史消息（针对该次 invite 的后续 cancel、accept、reject、timeout 操作也同样不会产生历史消息）。
	// 	offlinePushInfo	离线推送信息，其中 desc 为必填字段，推送的时候会默认展示 desc 信息。
	// 	timeout	超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发 onInvitationTimeout 回调
	// 	返回
	// 	inviteID 邀请 ID，如果邀请失败，返回 null 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static FString Invite(const FString& invitee, const FString& data, bool onlineUserOnly, const FTIMOfflinePushInfo& offlinePushInfo, int32 timeout, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	邀请群内的某些人
	//
	// 	参数
	// 	groupID	发起邀请所在群组
	// 	inviteeList	被邀请人列表，inviteeList 必须已经在 groupID 群里，否则邀请无效
	// 	onlineUserOnly	是否只有在线用户才能收到邀请，如果设置为 true，只有在线用户才能收到， 并且 invite 操作也不会产生历史消息（针对该次 invite 的后续 cancel、accept、reject、timeout 操作也同样不会产生历史消息）。
	// 	timeout	超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发 onInvitationTimeout 回调
	// 	返回
	// 	inviteID 邀请 ID，如果邀请失败，返回 null
	// 	注意
	// 	群邀请暂不支持离线推送，如果您需要离线推送，可以针对被邀请的用户单独发离线推送自定义消息， 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static FString InviteInGroup(const FString& groupID, const TArray<FString>& inviteeList, const FString& data, bool onlineUserOnly, int timeout, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 	
	// 	邀请方取消邀请
	//
	// 	参数
	// 	inviteID	邀请 ID
	// 	注意
	// 	如果所有被邀请人都已经处理了当前邀请（包含超时），不能再取消当前邀请。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static void Cancel(const FString& inviteID, const FString& data, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	接收方接收邀请
	//
	// 	注意
	// 	不能接受不是针对自己的邀请，请在收到 onReceiveNewInvitation 回调的时候先判断 inviteeList 有没有自己，如果没有自己，不能 accept 邀请。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static void Accept(const FString& inviteID, const FString& data, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	接收方拒绝邀请
	//
	// 	注意
	// 	不能拒绝不是针对自己的邀请，请在收到 onReceiveNewInvitation 回调的时候先判断 inviteeList 有没有自己，如果没有自己，不能 reject 邀请。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static void Reject(const FString& inviteID, const FString& data, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	获取信令信息
	//
	// 	如果 invite 设置 onlineUserOnly 为 false，每次信令操作（包括 invite、cancel、accept、reject、timeout）都会产生一条自定义消息， 该消息会通过 V2TIMAdvancedMsgListener -> onRecvNewMessage 抛给用户，用户也可以通过历史消息拉取，如果需要根据信令信息做自定义化文本展示，可以调用下面接口获取信令信息。
	//
	// 	参数
	// 	msg	消息对象
	// 	返回
	// 	V2TIMSignalingInfo 信令信息，如果为 null，则 msg 不是一条信令消息。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static FTIMSignalingInfo GetSignalingInfo(const FTIMMessage& msg);

	
	// 	/* 
	// 	添加邀请信令（可以用于群离线推送消息触发的邀请信令）
	//
	// 	在离线推送的场景下：
	//
	// 	针对 1V1 信令邀请，被邀请者 APP 如果被 Kill，当 APP 收到信令离线推送再次启动后，SDK 可以自动同步到邀请信令，如果邀请还没超时， 用户会收到 onReceiveNewInvitation 回调，如果邀请已经超时，用户还会收到 onInvitationTimeout 回调。
	// 	针对群信令邀请，被邀请者 APP 如果被 Kill，当 APP 收到离线推送再次启动后，SDK 无法自动同步到邀请信令（邀请信令本质上就是一条自定义消息，群离线消息在程序启动后无法自动同步）， 也就没法处理该邀请信令。如果被邀请者需要处理该邀请信令，可以让邀请者在发起信令的时候对针对每个被邀请者再单独发送一条 C2C 离线推送消息，消息里面携带 V2TIMSignalingInfo 信息， 被邀请者收到离线推送的时候把 V2TIMSignalingInfo 信息再通过 addInvitedSignaling 接口告知 SDK。
	// 	TUIKit 音视频通话离线推送功能基于这个接口实现，详细实现方法请参考文档：集成音视频通话
	//
	// 	注意
	// 	如果添加的信令信息已存在，callback 会抛 ERR_SDK_SIGNALING_ALREADY_EXISTS 错误码。
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMSignalingManager")
	static void AddInvitedSignaling(const FTIMSignalingInfo& info, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//



	/* 	
	1.3 获取会话列表

	一个会话对应一个聊天窗口，比如跟一个好友的 1v1 聊天，或者一个聊天群，都是一个会话。
	由于历史的会话数量可能很多，所以该接口希望您采用分页查询的方式进行调用，每次分页拉取的个数建议为 100 个。
	该接口拉取的是本地缓存的会话，如果服务器会话有更新，SDK 内部会自动同步，然后在 V2TIMConversationListener 回调告知客户。
	如果会话全部拉取完毕，成功回调里面 V2TIMConversationResult 中的 isFinished 获取字段值为 YES。
	注意
	会话排序规则
	5.5.892 及以后版本, 该接口获取的会话列表默认已经按照会话 orderKey 做了排序，orderKey 值越大，代表该会话排序越靠前。
	5.5.892 以前版本，该接口获取的会话列表默认已经按照会话 lastMessage -> timestamp 做了排序，timestamp 越大，会话越靠前。
	参数
	nextSeq	分页拉取的游标，第一次默认取传 0，后续分页拉传上一次分页拉取成功回调里的 nextSeq
	count	分页拉取的个数，一次分页拉取不宜太多，会影响拉取的速度，建议每次拉取 100 个会话 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void GetConversationList(const FString& nextSeq, int32 count, FMTIMConversationResultCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	/* 
	1.4 获取单个会话
	参数
	conversationID	会话唯一 ID, C2C 单聊组成方式：[NSString stringWithFormat:"c2c_%",userID]；群聊组成方式为 [NSString stringWithFormat:"group_%",groupID]
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void GetConversation(const FString& conversationID, FTIMConversationCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	1.5 获取指定会话列表

	参数
	conversationIDList	会话唯一 ID 列表，C2C 单聊组成方式：[NSString stringWithFormat:"c2c_%",userID]；群聊组成方式为 [NSString stringWithFormat:"group_%",groupID]
	 */
	//todo list
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void GetConversationListByIDList(const TArray<FString>& conversationIDList, FTIMConversationVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//GetConversationList
	//void GetConversationListByFilter(const V2TIMConversationListFilter& filter, V2TIMValueCallback<V2TIMConversationResult>* callback);


	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void DeleteConversation(const FString& conversationID, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	1.8 设置会话草稿
	//
	// 	参数
	// 	conversationID	会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:"c2c_%",userID]；群聊组成方式为 [NSString stringWithFormat:"group_%",groupID]
	// 	只在本地保存，不会存储 Server，不能多端同步，程序卸载重装会失效。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void SetConversationDraft(const FString& conversationID, const FString& draftText, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	// 		//void SetConversationCustomData(const TArray<FString>& conversationIDList, const V2TIMBuffer& customData, V2TIMValueCallback<V2TIMConversationOperationResultVector>* callback);
	//
	//
	// 	/* 
	// 	1.10 设置会话置顶（5.3.425 及以上版本支持）
	//
	// 	参数
	// 	conversationID	会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:"c2c_%",userID]；群聊组成方式为 [NSString stringWithFormat:"group_%",groupID]
	// 	isPinned	是否置顶 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	static void PinConversation(const FString& conversationID, bool isPinned, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	// 		//void MarkConversation(const TArray<FString>& conversationIDList, uint64_t markType, bool enableMark, V2TIMValueCallback<V2TIMConversationOperationResultVector>* callback);
	//
	//
	// 	/* 
	// 	1.12 获取所有会话的未读消息总数（5.3.425 及以上版本支持）
	//
	// 	注意
	// 	未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 V2TIMMessage.V2TIM_NOT_RECEIVE_MESSAGE 或 V2TIMMessage.V2TIM_RECEIVE_NOT_NOTIFY_MESSAGE 的会话。 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMConversationManager")
	//static void GetTotalUnreadMessageCount(V2TIMValueCallback<uint64_t>* callback);
	static void GetTotalUnreadMessageCount(FTIMuint64Callback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	// 		//void CreateConversationGroup(const FString& groupName, const TArray<FString>& conversationIDList, V2TIMValueCallback<V2TIMConversationOperationResultVector>* callback);
	//
	// 		//void GetConversationGroupList(V2TIMValueCallback<TArray<FString>>* callback);
	//
	// 		//void DeleteConversationGroup(const FString& groupName, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	// 		//void RenameConversationGroup(const FString& oldName, const FString& newName, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	// 		//void AddConversationsToGroup(const FString& groupName, const TArray<FString>& conversationIDList, V2TIMValueCallback<V2TIMConversationOperationResultVector>* callback);
	//
	// 		//void DeleteConversationsFromGroup(const FString& groupName, const TArray<FString>& conversationIDList, V2TIMValueCallback<V2TIMConversationOperationResultVector>* callback);
	//
	//










	
	// 	
	// 		/* 
	// 		2.2 获取指定好友资料
	// 	
	// 		参数
	// 		userIDList	好友 userID 列表
	// 		ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
	// 		*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void GetFriendsInfo(const TArray<FString>& userIDList, FTIMFriendInfoResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	/* 
	2.3 设置指定好友资料 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void SetFriendInfo(const FTIMFriendInfo& info, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);

	// 	/* 
	// 	2.4 搜索好友（5.4.666 及以上版本支持）
	//
	// 	注意
	// 	接口返回本地存储的用户资料，可以根据 V2TIMFriendInfoResult 中的 getRelation 来判断是否为好友。
	// 	该功能为 IM 旗舰版功能，购买旗舰版套餐包后可使用，详见价格说明 
	// 	*/

	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	//static void SearchFriends(const V2TIMFriendSearchParam& searchParam, V2TIMValueCallback<V2TIMFriendInfoResultVector>* callback);
	static void SearchFriends(const FTIMFriendSearchParam& searchParam, FTIMFriendInfoResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	/* 
	2.5 添加好友
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void AddFriend(const FTIMFriendAddApplication& application, FTIMFriendOperationResulCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	2.6 删除好友

	参数
	userIDList	要删除的好友 userID 列表
	ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
	deleteType	删除类型（单向好友、双向好友）
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void DeleteFromFriendList(const TArray<FString>& userIDList, ETIMFriendType deleteType, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	2.7 检查指定用户的好友关系

	参数
	userIDList	要检查的 userID 列表
	checkType	检查类型 （单向好友检查、双向好友检查）
	succ	成功后的回调
	fail	失败后的回调
	注意
	checkType 的使用需要注意：
	checkType 如果传入 V2TIM_FRIEND_TYPE_SINGLE，结果返回：V2TIM_FRIEND_RELATION_TYPE_NONE、V2TIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST 两种情况
	checkType 如果传入 V2TIM_FRIEND_TYPE_BOTH，结果返回：V2TIM_FRIEND_RELATION_TYPE_NONE、V2TIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST、 V2TIM_FRIEND_RELATION_TYPE_IN_OTHER_FRIEND_LIST、V2TIM_FRIEND_RELATION_TYPE_BOTH_WAY 四种情况 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void CheckFriend(const TArray<FString>& userIDList, ETIMFriendType checkType, FTIMFriendCheckResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	3.1 获取好友申请列表

	注意
	好友申请列表包括发起的好友申请和收到的好友申请。
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void GetFriendApplicationList(FTIMFriendApplicationResultCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	3.2 同意好友申请

	参数
	application	好友申请信息，getFriendApplicationList 成功后会返回
	acceptType	建立单向/双向好友关系 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void AcceptFriendApplication(const FTIMFriendApplication& application, ETIMFriendAcceptType acceptType, FTIMFriendOperationResulCallback OnSuccessDelegate,FIMFailureCallback OnFailureDelegate);


	/* 
	3.3 拒绝好友申请

	参数
	application	好友申请信息，getFriendApplicationList 成功后会返回 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void RefuseFriendApplication(const FTIMFriendApplication& application, FTIMFriendOperationResulCallback OnSuccessDelegate,FIMFailureCallback OnFailureDelegate);


	/* 
	3.4 删除好友申请

	参数
	application	好友申请信息，getFriendApplicationList 成功后会返回
	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void DeleteFriendApplication(const FTIMFriendApplication& application, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);


	/* 
	3.5 设置好友申请已读 
	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	//static void SetFriendApplicationRead(V2TIMCallback* callback);
	static void SetFriendApplicationRead(FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	
	//
	// 	/* 
	// 	4.1 添加用户到黑名单 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void AddToBlackList(const TArray<FString>& userIDList, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	4.2 把用户从黑名单中删除
	// 	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void DeleteFromBlackList(const TArray<FString>& userIDList, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	4.3 获取黑名单列表
	// 	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void GetBlackList(FTIMFriendInfoVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.1 新建好友分组
	//
	// 	参数
	// 	groupName	分组名称
	// 	userIDList	要添加到分组中的好友
	// 	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void CreateFriendGroup(const FString& groupName, const TArray<FString>& userIDList, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.2 获取分组信息
	//
	// 	参数
	// 	groupNameList	要获取信息的好友分组名称列表,传入 nil 获得所有分组信息
	// 	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void GetFriendGroups(const TArray<FString>& groupNameList, FTIMFriendGroupVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.3 删除好友分组
	// 	 */
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void DeleteFriendGroup(const TArray<FString>& groupNameList, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.4 修改好友分组的名称 
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void RenameFriendGroup(const FString& oldName, const FString& newName, FIMCallbackDelegate OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.5 添加好友到一个好友分组
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void AddFriendsToFriendGroup(const FString& groupName, const TArray<FString>& userIDList, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//
	// 	/* 
	// 	5.6 从好友分组中删除好友
	// 	*/
	UFUNCTION(BlueprintCallable, Category = "TencentIMLink|IMFriendshipManager")
	static void DeleteFriendsFromFriendGroup(const FString& groupName, const TArray<FString>& userIDList, FTIMFriendOperationResultVectorCallback OnSuccessDelegate, FIMFailureCallback OnFailureDelegate);
	//
	//


public:
	//------------
	//Base function
	static FTIMConversationResult ToTIMConversationResult(const V2TIMConversationResult& ConversationResult);
	static V2TIMVConversationVector ToV2TIMVConversationVector(const TArray<FTIMConversation>& Array_Conversation);
	static TArray<FTIMConversation> ToTIMConversationArray(const V2TIMVConversationVector& ConversationVector);
	static V2TIMConversation ToTIMConversation(const FTIMConversation& Conversation);
	static FTIMConversation ToConversation(const V2TIMConversation& Conversation);

	static TArray<FTIMGroupAtInfo> ToGroupAtInfoArray(const V2TIMGroupAtInfoVector& GroupAtInfoVector);
	static V2TIMGroupAtInfoVector ToTIMGroupAtInfoVector(const TArray<FTIMGroupAtInfo>& GroupAtInfoVector);

	static FTIMGroupAtInfo  ToGroupAtInfo(const V2TIMGroupAtInfo& GroupAtInfo);
	static V2TIMGroupAtInfo  ToTIMGroupAtInfo(const FTIMGroupAtInfo& GroupAtInfo);

	static ETIMGroupAtType ToGroupAtType(const V2TIMGroupAtType& GroupType);
	static V2TIMGroupAtType ToTIMGroupAtType(const ETIMGroupAtType& GroupType);

	static ETIMConversationType ToConversationType(const V2TIMConversationType& ConvType);
	static V2TIMConversationType ToTimConversationType(const ETIMConversationType& ConvType);

	static TArray<FTIMFriendInfo> ToFriendInfoArray(const V2TIMFriendInfoVector& Info);

	static TArray<FTIMFriendInfoResult> ToFriendInfoResultArray(const V2TIMFriendInfoResultVector& FriendInfoResultVector);
	static FTIMFriendInfoResult ToFriendInforResult(const V2TIMFriendInfoResult& FriendInfoResult);

	static FTIMFriendInfo ToFriendInfo(const V2TIMFriendInfo& Info);
	static V2TIMFriendInfo ToTIMFriendInfo(const FTIMFriendInfo& Info);

	static V2TIMFriendSearchParam ToTIMFriendSearchParam(const FTIMFriendSearchParam& FriendSearchParam);

	static FTIMFriendOperationResult ToFriendOperationResult(const V2TIMFriendOperationResult& FriendOperationResult);

	static V2TIMFriendType ToTIMFriendType(ETIMFriendType Type);

	static V2TIMFriendAddApplication ToTIMFriendAddApplication(const FTIMFriendAddApplication& FriendAddApplication);

	static TArray<FTIMFriendOperationResult> ToTIMFriendOperationResultArray(const V2TIMFriendOperationResultVector& TIMFriendOperationResultVector);

	static TArray<FTIMFriendCheckResult> ToTIMFriendCheckResultArray(const V2TIMFriendCheckResultVector& TIMFriendCheckResultVector);

	static V2TIMFriendCheckResultVector ToV2TIMFriendCheckResultVector(const TArray<FTIMFriendCheckResult>& TIMFriendCheckResult);
	static V2TIMFriendCheckResult ToV2TIMFriendCheckResult(const FTIMFriendCheckResult& FriendCheckResult);
	static FTIMFriendCheckResult ToFTIMFriendCheckResult(const V2TIMFriendCheckResult& FriendCheckResult);

	static V2TIMGroupMemberInfoResult ToTIMGroupMemberInfoResult(const FTIMGroupMemberInfoResult& Result);
	static FTIMGroupMemberInfoResult ToV2TIMGroupMemberInfoResult(const V2TIMGroupMemberInfoResult& Result);

	//群组相关
	static FTIMGroupMemberInfo ToTIMGroupMemberInfo(const V2TIMGroupMemberInfo& GroupMemberInfo);
	
	static TArray<FTIMGroupMemberInfo> ToTIMGroupMemberInfoArray(const V2TIMGroupMemberInfoVector& GroupMemberInfo);

	static FTIMGroupMemberChangeInfo ToTIMGroupMemberChangeInfo(const V2TIMGroupMemberChangeInfo& MemberChangeInfo);
	
	static TArray<FTIMGroupMemberChangeInfo> ToTIMGroupMemberChangeInfoArray(const V2TIMGroupMemberChangeInfoVector& MemberChangeInfo);

	static ETIMGroupInfoChangeType ToTIMGroupInfoChangeType(const V2TIMGroupInfoChangeType& GroupInfo);

	static FTIMGroupChangeInfo ToTIMGroupChangeInfo (const V2TIMGroupChangeInfo& GroupChangeInfo);
	static TArray<FTIMGroupChangeInfo> ToTIMGroupChangeInfoArray (const V2TIMGroupChangeInfoVector& GroupChangeInfo);
	
	//玩家请求相关
	static TArray<FTIMFriendApplication> ToTIMFriendApplicationArray(const V2TIMFriendApplicationVector& FriendApplicationVector);

	
	static ETIMFriendRelationType ToTIMFriendRelationType(const V2TIMFriendRelationType& Type);
	
	static FTIMFriendApplication ToTIMFriendApplication(const V2TIMFriendApplication& IMFriendApplication);
	static FTIMFriendApplicationResult ToTIMFriendApplicationResult(const V2TIMFriendApplicationResult& TIMFriendApplicationResult);

	static V2TIMGroupMemberFullInfoVector ToTIMGroupMemberFullInfoVector(const TArray<FTIMGroupMemberFullInfo>& GroupMemberFullInfoArray);
	static TArray<FTIMGroupMemberFullInfo> ToFTIMGroupMemberFullInfoArray(const V2TIMGroupMemberFullInfoVector& GroupMemberFullInfoVector);
	static V2TIMGroupMemberFullInfo ToV2TIMGroupMemberFullInfo(const FTIMGroupMemberFullInfo& Info);
	static FTIMGroupMemberFullInfo ToTIMGroupMemberFullInfo(const V2TIMGroupMemberFullInfo& Info);

	static ETIMGroupMemberResult ToTIMGroupMemberResult(const V2TIMGroupMemberResult& Result);
	
	static FTIMGroupMemberOperationResult ToTIMGroupMemberOperationResult(const V2TIMGroupMemberOperationResult& Result);
	
	static V2TIMFriendApplication ToV2TIMFriendApplication(const FTIMFriendApplication& TIMFriendApplication);
	
	static ETIMFriendApplicationType ToTIMFriendApplicationType(const V2TIMFriendApplicationType& Type);

	static V2TIMFriendApplicationType ToV2TIMFriendApplicationType(const ETIMFriendApplicationType& Type);

	static TArray<FTIMFriendGroup> ToTIMFriendGroupArray(const V2TIMFriendGroupVector& TIMFriendGroup);

	static FTIMFriendGroup ToTIMFriendGroup(const V2TIMFriendGroup& Group);

	static V2TIMOfflinePushInfo ToTIMOfflinePushInfo(const FTIMOfflinePushInfo& Info);

	static V2TIMSignalingInfo ToTIMSignalingInfo(const FTIMSignalingInfo& Info);
	
	static FTIMSignalingInfo ToSignalingInfo(const V2TIMSignalingInfo& Info);
	
	static V2TIMFriendAcceptType ToV2TIMFriendAcceptType (const ETIMFriendAcceptType& Type);
	
	static V2TIMString ToIMString(const FString& InStr);

	static FString ToFString(const V2TIMString& InStr);
	

	static V2TIMStringVector ToIMStringVector(TArray<FString> InStrArray);

	static TArray<FString> ToFStringArray(V2TIMStringVector TIMStringVector);
	
	static TMap<FString,FString> ToFStringMap(V2TIMGroupAttributeMap TIMStringVector);
	
	static V2TIMSignalingActionType ToV2TIMSignalingActionType(const ETIMSignalingActionType& Type);
	
	static ETIMSignalingActionType ToTIMSignalingActionType(const V2TIMSignalingActionType& Type);
	
	static ELoginStatus ToTIMLoginStatus(const V2TIMLoginStatus& Status);

	static V2TIMMessagePriority GetMessagePriority(EIMMessagePriority InPriority);

	static FTIMUserFullInfo ToTIMUserFullInfo(const V2TIMUserFullInfo& info);

	static V2TIMUserFullInfo ToV2TIMUserFullInfo(const FTIMUserFullInfo& info);

	static ETIMGender ToTIMGender(V2TIMGender Gender);

	static ETIMFriendAllowType ToTIMAllowType(V2TIMFriendAllowType AllowType);

	static V2TIMFriendAllowType ToV2TIMAllowType(const ETIMFriendAllowType& AllowType);

	static TMap<FString, FBuffer> ToTIMCustomInfo_(V2TIMCustomInfo CustomInfo);

	static FBuffer ToBuffer(V2TIMBuffer TIMBuffer);

	static V2TIMBuffer ToTIMBuffer(FBuffer TIMBuffer);

	static V2TIMCustomInfo ToV2TIMCustomInfo(TMap<FString, FBuffer> CustomInfo);

	static TMap<FString, V2TIMBuffer> ToTIMCustomInfo(V2TIMCustomInfo CustomInfo);

	static V2TIMCustomInfo ToV2TIMCustomInfo(TMap<FString, V2TIMBuffer> CustomInfo);

	static TArray<FTIMUserFullInfo> ToTIMUserFullInfoArray(const V2TIMUserFullInfoVector& FullInfoVector);

	static V2TIMMessage ToIMMessage(const FTIMMessage& TimMessage);

	static FTIMMessage ToMessage(const V2TIMMessage& TimMessage);
	
	static V2TIMMessageStatus ToTimMessageStatus(const ETIMMessageStatus& MessageStatus);

	static TArray<FTIMMessage> ToMessageArray(const V2TIMMessageVector& MessageVector);

	static V2TIMMessageVector ToV2IMMessageArray(const TArray<FTIMMessage>& MessageArray);

	static V2TIMReceiveMessageOpt ToTIMReceiveMessageOpt(const ETIMReceiveMessageOpt& MsgOpt);

	static ETIMReceiveMessageOpt ToReceiveMessageOpt(const V2TIMReceiveMessageOpt& MsgOpt);


	static FTIMReceiveMessageOptInfo ToReceiveMessageOptInfo(const V2TIMReceiveMessageOptInfo& OptInfo);

	static V2TIMReceiveMessageOptInfo ToTIMReceiveMessageOptInfo(const FTIMReceiveMessageOptInfo& OptInfo);


	static TArray<FTIMReceiveMessageOptInfo> ToReceiveMessageOptInfoArray(const V2TIMReceiveMessageOptInfoVector& MessageOptInfoVector);


	static V2TIMMessageListGetOption ToIMMessageListGetOption(const FTIMMessageListGetOption& Option);

	static ETIMMessageGetType ToMessageGetType(V2TIMMessageGetType& MessageType);
	static V2TIMMessageGetType ToTIMMessageGetType(const ETIMMessageGetType& MessageType);

	static V2TIMMessageSearchParam ToTIMessageSearchParam(const FTIMMessageSearchParam& MessageSearchParam);

	static ETIMKeywordListMatchType ToKeywordListMatchType(const V2TIMKeywordListMatchType& MessageSearchParam);

	static V2TIMKeywordListMatchType ToTIMKeywordListMatchType(const ETIMKeywordListMatchType& MessageSearchParam);

	static FTIMElem ToElem(const V2TIMElem& TimElem);
	
	static V2TIMElem ToTIMElem(const FTIMElem& TimElem);

	// static TArray<FTIMElem> ToTIMElemArray(const V2TIMElemVector& ElementVector);
	static TArray<FString> ToTIMElemStringArray(const V2TIMElemVector& ElementVector);
	static V2TIMElemVector ToElemVector(const TArray<FString>& ElementVector);

	static V2TIMElemType ToTIMElemType(const ETIMElemType& MessageSearchParam);

	static ETIMElemType ToElemType(const V2TIMElemType& MessageSearchParam);

	static V2TIMElemTypeVector ToTIMElemTypeVector(const TArray<ETIMElemType>& MessageSearchParam);

	static TArray<ETIMElemType> ToElemTypeArray(const V2TIMElemTypeVector& MessageSearchParam);

	static FTIMMessageSearchResult ToMessageSearchResult(const V2TIMMessageSearchResult& MessageSearchResult);

	static TArray<FTIMMessageSearchResultItem> ToMessageResultItem(const V2TIMMessageSearchResultItemVector& MessageResult);

	static FTIMMessageSearchResultItem ToMessageSearchResultItem(const V2TIMMessageSearchResultItem& TIMMessageSearchResultItem);

	//-------------------------
	//Group Info
	static ETIMGroupAddOpt  ToGroupAddOpt(const V2TIMGroupAddOpt& GroupAddOpt);
	static V2TIMGroupAddOpt  ToTIMGroupAddOpt(const ETIMGroupAddOpt& GroupAddOpt);

	static FTIMGroupInfo ToGroupInfo(const V2TIMGroupInfo& GroupInfo);

	static V2TIMGroupInfo ToTIMGroupInfo(const FTIMGroupInfo& GroupInfo);

	static FTIMCreateGroupMemberInfo  ToGroupMemberInfo(const V2TIMCreateGroupMemberInfo& GroupMemberInfo);
	static V2TIMCreateGroupMemberInfo  ToIMGroupMemberInfo(const FTIMCreateGroupMemberInfo& GroupMemberInfo);

	static TArray<FTIMCreateGroupMemberInfo> ToGroupMemberInfoArray(const V2TIMCreateGroupMemberInfoVector& MemberInfoVector);
	static V2TIMCreateGroupMemberInfoVector ToCreateGroupMemberInfoVector(const TArray<FTIMCreateGroupMemberInfo>& MemberInfoVector);
};



