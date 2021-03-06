//
//  PgSQLValue.h
//  PgTest
//
//  Created by eien.support@gmail.com on 11/08/27.
//  Copyright (c) 2011 "Eien Factory". All rights reserved.
//

#import <Foundation/Foundation.h>

#include "libpq-fe.h"

#ifndef INT8OID
#define INVALID_OID (-1)
#define  INT8OID   20
#define  INT2OID   21
#define  INT4OID   23
#define	 BOOLOID	16
#define  FLOAT4OID   700
#define  FLOAT8OID   701
#define  VARCHAROID   1043
#define	 TEXTOID	25
#define  DATEOID   1082
#define  TIMEOID   1083
#define  TIMESTAMPOID   1114
#define  TIMESTAMPTZOID   1184
#endif

@interface PgSQLValue : NSObject
{
    id value_;
    Oid type_;
}
@property(nonatomic,retain,readwrite) id value;
@property(nonatomic,assign,readwrite) Oid type;

- (id)initWithBinary:(const char *)val type:(Oid)type;
+ (PgSQLValue*)valueWithBinary:(const char *)val type:(Oid)type;
- (id)initWithObject:(id)val type:(Oid)type;
+ (PgSQLValue*)valueWithObject:(id)val type:(Oid)type;
- (void)setObject:(id)val type:(Oid)type;
- (size_t)getBinarySize;
- (size_t)getBufferSize;
- (size_t)getBinary:(char *)buff maxSize:(size_t)size;
- (id)objectValue;
- (char *)cStringValue;// must free
- (int32_t)intValue;
- (int64_t)longLongValue;
- (float)floatValue;
- (double)doubleValue;
- (time_t)timetValue;
- (NSDate*)dateValue;
- (NSString*)stringValue;
- (BOOL)boolValue;
- (NSData*)dataValue;

- (void)setBoolValue:(BOOL)val;
- (void)setByteValue:(int8_t)val;
- (void)setShortValue:(int16_t)val;
- (void)setIntValue:(int32_t)val;
- (void)setLongLongValue:(int64_t)val;
- (void)setFloatValue:(float)val;
- (void)setDoubleValue:(double)val;
- (void)setDate:(NSDate*)aDate;
- (void)setTime:(NSDate*)aDate;
- (void)setTimestamp:(NSDate*)aDate;
- (void)setTimestampTZ:(NSDate*)aDate;
- (void)setString:(NSString*)aString;
- (void)setText:(NSString*)aString;
- (void)setData:(NSData*)object;

- (NSString*)description;
- (BOOL)isNullValue;

@end
