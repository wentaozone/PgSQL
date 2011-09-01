//
//  PgSQLUpdate.m
//  PgTest
//
//  Created by 黒木 政幸 on 11/08/27.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "PgSQLUpdate.h"

@implementation PgSQLUpdate

+ (PgSQLUpdate*)updateCommandWith:(PgSQLRecord*)aRecord connection:(PgSQLConnection*)con
{
    if ( ![aRecord isKindOfClass:[PgSQLRecord class]] ) return nil;
    if ( aRecord.tableName == nil ) return nil;
    if ( aRecord.pkeyName == nil ) return nil;
    if ( [aRecord.attributes count] == 0 ) return nil;
    PgSQLUpdate *anObject = [[PgSQLUpdate alloc] init];
    anObject.conn = con;
    anObject.record = aRecord;
    return [anObject autorelease];
}

- (PgSQLResult*)execute
{
    NSString *sql;
    NSMutableArray *keys;
    NSArray *values;
    if ( ![self isBinary] ) return nil;
    if ( record_.tableName == nil ) return nil;
    if ( record_.pkeyName == nil ) return nil;
    if ( [record_.attributes count] == 0 ) return nil;
    keys = [NSMutableArray arrayWithCapacity:[record_.attributes count]];
    [[record_.attributes allKeys] enumerateObjectsUsingBlock:^(id obj,NSUInteger idx,BOOL *stop){
        if ( ![obj isEqualToString:record_.pkeyName] ) {
            [keys addObject:obj];
        }
    }];
    NSString *keyList = [keys componentsJoinedByString:@", "];
    [keys addObject:record_.pkeyName];
    values = [record_.attributes objectsForKeys:keys notFoundMarker:[NSNull null]];
    self.params = values;
    NSMutableArray *params = [NSMutableArray arrayWithCapacity:[keys count]];
    for ( int i = 0; i < [keys count]-1; i++ ) {
        [params addObject:[NSString stringWithFormat:@"$%d",i+1]];
    }
    NSString *paramList = [params componentsJoinedByString:@", "];
    NSString *whereStatement = [NSString stringWithFormat:@"%@ = $%d",record_.pkeyName,[keys count]];
    sql = [NSString stringWithFormat:@"UPDATE %@ SET ( %@ ) = ( %@ ) WHERE %@;",
           record_.tableName, keyList, paramList, whereStatement ];
    NSLog(@"%@",sql);
    return [PgSQLCommand executeBinaryFormat:sql params:params_ connection:conn_];
}

@end
