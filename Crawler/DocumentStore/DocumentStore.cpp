#include "DocumentStore.hpp"

DocumentStore::DocumentStore(std::shared_ptr<mysqlx::Client> client) {
    this->client = client;
}

std::vector<Document> DocumentStore::getAll() const {
    std::vector<Document> all;
    
    auto session = this->client->getSession();
    
    {
        auto sessionRes = session
        .getDefaultSchema()
        .getTable("documents")
        .select("url", "title", "description", "allText")
        .execute();
        
        mysqlx::Row row;
        while ((row = sessionRes.fetchOne())) {
            all.push_back(Document((std::string)row[0], (std::string)row[1], (std::string)row[2], (std::string)row[3]));
        }
    }
    
    session.close();
    return all;
}

void DocumentStore::save(const Document& document) {
    
    auto session = this->client->getSession();

    {
        auto table = session.getDefaultSchema()
        .getTable("documents");
        
        auto sessionRes = table
        .select("url")
        .where("url = :url")
        .bind("url", document.getUrl())
        .execute();
        
        if (sessionRes.count() == 0) {
            auto sessionRes = table
            .insert("url", "title", "description", "allText")
            .values(document.getUrl(), document.getTitle(), document.getDescription(), document.getAllText())
            .execute();
        }
    }
    
    session.close();
    
}

std::size_t DocumentStore::count() const {
    auto session = this->client->getSession();
    
    std::size_t count = 0;
    
    {
        count = session.getDefaultSchema()
        .getTable("documents")
        .count();
    }
    
    session.close();
    
    return count;
}
