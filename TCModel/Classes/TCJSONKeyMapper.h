//
//  JSONKeyMapper.h
//  JSONModel
//

#import <Foundation/Foundation.h>

typedef NSString *(^TCModelKeyMapBlock)(NSString *keyName);

/**
 * **You won't need to create or store instances of this class yourself.** If you want your model
 * to have different property names than the JSON feed keys, look below on how to
 * make your model use a key mapper.
 *
 * For example if you consume JSON from twitter
 * you get back underscore_case style key names. For example:
 *
 * <pre>"profile_sidebar_border_color": "0094C2",
 * "profile_background_tile": false,</pre>
 *
 * To comply with Obj-C accepted camelCase property naming for your classes,
 * you need to provide mapping between JSON keys and ObjC property names.
 *
 * In your model overwrite the + (JSONKeyMapper *)keyMapper method and provide a JSONKeyMapper
 * instance to convert the key names for your model.
 *
 * If you need custom mapping it's as easy as:
 * <pre>
 * + (JSONKeyMapper *)keyMapper {
 * &nbsp; return [[JSONKeyMapper&nbsp;alloc]&nbsp;initWithDictionary:@{@"crazy_JSON_name":@"myCamelCaseName"}];
 * }
 * </pre>
 * In case you want to handle underscore_case, **use the predefined key mapper**, like so:
 * <pre>
 * + (JSONKeyMapper *)keyMapper {
 * &nbsp; return [JSONKeyMapper&nbsp;mapperFromUnderscoreCaseToCamelCase];
 * }
 * </pre>
 */
@interface TCJSONKeyMapper : NSObject

/** @name Name converters */
/** Block, which takes in a property name and converts it to the corresponding JSON key name */
@property (readonly, nonatomic) TCModelKeyMapBlock modelToJSONKeyBlock;

/** Combined converter method
 * @param value the source name
 * @return JSONKeyMapper instance
 */
- (NSString *)convertValue:(NSString *)value;

/** @name Creating a key mapper */

/**
 * Creates a JSONKeyMapper instance, based on the block you provide this initializer.
 * The parameter takes in a JSONModelKeyMapBlock block:
 * <pre>NSString *(^JSONModelKeyMapBlock)(NSString *keyName)</pre>
 * The block takes in a string and returns the transformed (if at all) string.
 * @param toJSON transforms your model property name to a JSON key
 */
- (instancetype)initWithModelToJSONBlock:(TCModelKeyMapBlock)toJSON;

/**
 * Creates a JSONKeyMapper instance, based on the mapping you provide.
 * Use your JSONModel property names as keys, and the JSON key names as values.
 * @param toJSON map dictionary, in the format: <pre>@{@"myCamelCaseName":@"crazy_JSON_name"}</pre>
 * @return JSONKeyMapper instance
 */
- (instancetype)initWithModelToJSONDictionary:(NSDictionary <NSString *, NSString *> *)toJSON;

/**
 * Given a camelCase model property, this mapper finds JSON keys using the snake_case equivalent.
 */
+ (instancetype)mapperForSnakeCase;

/**
 * Given a camelCase model property, this mapper finds JSON keys using the TitleCase equivalent.
 */
+ (instancetype)mapperForTitleCase;

/**
 * Creates a JSONKeyMapper based on a built-in JSONKeyMapper, with specific exceptions.
 * Use your JSONModel property names as keys, and the JSON key names as values.
 */
+ (instancetype)baseMapper:(TCJSONKeyMapper *)baseKeyMapper withModelToJSONExceptions:(NSDictionary *)toJSON;

@end
