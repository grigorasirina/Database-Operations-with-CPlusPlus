#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>

int main() {
    mongocxx::instance instance{}; // Initialize the MongoDB C++ driver
    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}}; // Connect to MongoDB

    // Step 1: Select a database and a collection
    mongocxx::database db = client["mydb"];
    mongocxx::collection coll = db["mycollection"];

    // Step 2: Insert data into the collection (CREATE operation)
    bsoncxx::builder::stream::document document;
    document << "name" << "Irina Grigoras" << "age" << 20;
    coll.insert_one(document.view());

    // Step 3: Read data from the collection (READ operation)
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        coll.find_one(bsoncxx::builder::stream::document{} << "name" << "Irina Grigoras" << bsoncxx::builder::stream::finalize);
    if (maybe_result) {
        bsoncxx::document::view result_view = maybe_result->view();
        std::cout << "Data selected successfully: " << bsoncxx::to_json(result_view) << std::endl;
    } else {
        std::cerr << "No matching document found." << std::endl;
    }

    // Step 4: Update data in the collection (UPDATE operation)
    bsoncxx::stdx::optional<mongocxx::result::update> result =
        coll.update_one(bsoncxx::builder::stream::document{} << "name" << "Irina Grigoras" << bsoncxx::builder::stream::finalize,
                        bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document
                                                             << "age" << 21 << bsoncxx::builder::stream::close_document
                                                             << bsoncxx::builder::stream::finalize);
    if (result) {
        std::cout << "Data updated successfully. Matched " << result->matched_count() << " document(s)." << std::endl;
    } else {
        std::cerr << "Update failed." << std::endl;
    }

    // Step 5: Delete data from the collection (DELETE operation)
    bsoncxx::stdx::optional<mongocxx::result::delete_result> delete_result =
        coll.delete_one(bsoncxx::builder::stream::document{} << "name" << "Irina Grigoras" << bsoncxx::builder::stream::finalize);
    if (delete_result) {
        std::cout << "Data deleted successfully. Matched " << delete_result->deleted_count() << " document(s)." << std::endl;
    } else {
        std::cerr << "Delete failed." << std::endl;
    }

    return 0;
}
