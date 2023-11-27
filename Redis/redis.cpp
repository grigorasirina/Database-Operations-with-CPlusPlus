#include <iostream>
#include <hiredis/hiredis.h>

int main() {
    // Step 1: Establish a connection to the Redis server
    redisContext *ctx = redisConnect("localhost", 6379);

    if (ctx == nullptr || ctx->err) {
        if (ctx) {
            std::cerr << "Connection error: " << ctx->errstr << std::endl;
            redisFree(ctx);
        } else {
            std::cerr << "Connection error: unable to allocate Redis context." << std::endl;
        }
        return 1;
    }

    // Step 2: Create and insert data into Redis (CREATE operation)
    const char *key = "user:1";
    const char *name = "John Doe";
    const char *age = "30";

    redisReply *reply = (redisReply *)redisCommand(ctx, "SET %s %s", key, name);
    if (reply == nullptr || ctx->err) {
        std::cerr << "SET failed: " << (reply ? reply->str : ctx->errstr) << std::endl;
        freeReplyObject(reply);
        redisFree(ctx);
        return 1;
    }
    freeReplyObject(reply);

    // Step 3: Read data from Redis (READ operation)
    reply = (redisReply *)redisCommand(ctx, "GET %s", key);
    if (reply == nullptr || ctx->err) {
        std::cerr << "GET failed: " << (reply ? reply->str : ctx->errstr) << std::endl;
        freeReplyObject(reply);
        redisFree(ctx);
        return 1;
    }
    std::cout << "Name: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Step 4: Update data in Redis (UPDATE operation)
    const char *newName = "Irina Grigoras";
    reply = (redisReply *)redisCommand(ctx, "SET %s %s", key, newName);
    if (reply == nullptr || ctx->err) {
        std::cerr << "SET failed: " << (reply ? reply->str : ctx->errstr) << std::endl;
        freeReplyObject(reply);
        redisFree(ctx);
        return 1;
    }
    freeReplyObject(reply);

    // Step 5: Read updated data from Redis (READ operation)
    reply = (redisReply *)redisCommand(ctx, "GET %s", key);
    if (reply == nullptr || ctx->err) {
        std::cerr << "GET failed: " << (reply ? reply->str : ctx->errstr) << std::endl;
        freeReplyObject(reply);
        redisFree(ctx);
        return 1;
    }
    std::cout << "Updated Name: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Step 6: Delete data from Redis (DELETE operation)
    reply = (redisReply *)redisCommand(ctx, "DEL %s", key);
    if (reply == nullptr || ctx->err) {
        std::cerr << "DEL failed: " << (reply ? reply->str : ctx->errstr) << std::endl;
        freeReplyObject(reply);
        redisFree(ctx);
        return 1;
    }
    freeReplyObject(reply);
    std::cout << "Data deleted successfully" << std::endl;

    // Step 7: Close the Redis connection
    redisFree(ctx);

    return 0;
}
