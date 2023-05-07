#include "DefineFields.h"

const QString DefineFields::funcType = "FUNC_TYPE";
const QString DefineFields::UserId = "USER_ID";
const QString DefineFields::PassWord = "PASSWORD";
const QString DefineFields::Mac = "MAC";
const QString DefineFields::FundListStr = "USER_ID_LIST";
const QString DefineFields::FundAccount = "fund_account";
const QString DefineFields::Admin_Account = "Admin_Account";
const QString DefineFields::Admin_Password = "Admin_Password";
const QString DefineFields::Ip = "ip";
const QString DefineFields::Port = "port";
const QString DefineFields::Admin = "Admin";
const QString DefineFields::sender = "sender";

const QString FuncType::Settings = "Settings";
const QString FuncType::Log = "Log";
const QString FuncType::AddTrader = "addTrader";
const QString FuncType::DeleteTrader = "deleteTrader";
const QString FuncType::AddFundAccount = "addFundAccount";
const QString FuncType::DeleteFundAccount = "deleteFundAccount";
const QString FuncType::ReadTraderMsg = "readTraderMsg";
const QString FuncType::ModifiTraderMsg = "modifiTraderMsg";

const QString MasterFileds::ret = "10008";
const QString MasterFileds::textDescribe = "58";

const QString MasterValues::ResponseResult::success = "0";
const QString MasterValues::ResponseResult::fail = "1";
const QString MasterValues::ResponseResult::timeOut = "2";

const QString MasterValues::LogInfo::beginRow = "10001";
const QString MasterValues::LogInfo::endRow = "10002";
const QString MasterValues::LogInfo::totalRow = "10003";
const QString MasterValues::LogInfo::currentPos= "10004";
const QString MasterValues::LogInfo::pathFileName= "10005";
const QString MasterValues::LogInfo::content = "10006";
