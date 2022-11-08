/*
 *  DyldInfo.h
 *  MachOView
 *
 *  Created by psaghelyi on 21/09/2010.
 *
 */

#import "MachOLayout.h"
#include <mach-o/fixup-chains.h>

@interface DyldHelper : NSObject
{
  NSMutableDictionary * externalMap; // external symbol name --> symbols index (negative number)
}

+(DyldHelper *) dyldHelperWithSymbols:(NSDictionary *)symbolNames is64Bit:(bool)is64Bit;

@end


@interface MachOLayout (DyldInfo)

enum BindNodeType {NodeTypeBind, NodeTypeWeakBind, NodeTypeLazyBind};

- (MVNode *)createRebaseNode:(MVNode *)parent
                     caption:(NSString *)caption
                    location:(uint32_t)location
                      length:(uint32_t)length
                 baseAddress:(uint64_t)baseAddress;

- (MVNode *)createBindingNode:(MVNode *)parent
                      caption:(NSString *)caption
                     location:(uint32_t)location
                       length:(uint32_t)length
                  baseAddress:(uint64_t)baseAddress
                     nodeType:(BindNodeType)nodeType
                   dyldHelper:(DyldHelper *)helper;

- (MVNode *)createExportNode:(MVNode *)parent
                     caption:(NSString *)caption
                    location:(uint32_t)location
                      length:(uint32_t)length
                 baseAddress:(uint64_t)baseAddress;

- (MVNode *)createFixupHeaderNode:(MVNode *)parent
                      caption:(NSString *)caption
                     location:(uint32_t)location
                           header:(struct dyld_chained_fixups_header const *)header;
- (MVNode *)createFixupImageNode:(MVNode *)parent
                         caption:(NSString *)caption
                        location:(uint32_t)location
                   startsInImage:(struct dyld_chained_starts_in_image const *)startsInImage;
- (MVNode *)createFixupImageSegmentNode:(MVNode *)parent
                         caption:(NSString *)caption
                        location:(uint32_t)location
                                 offset:(uint32_t)offset
                        startsInSegment:(struct dyld_chained_starts_in_segment const *)startsInSegment;

- (MVNode *)createFixupPageStartsNode:(MVNode *)parent
                         caption:(NSString *)caption
                        location:(uint32_t)location
                        pageIndex:(uint32_t)pageIndex
                           fixup_base:(uint32_t)fixup_base
                              segname:(const char *)segname
                      header:(struct dyld_chained_fixups_header const *)header
                      startsInSegment:(struct dyld_chained_starts_in_segment const *)startsInSegment;

@end
