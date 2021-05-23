#include "LinkStore.hpp"

LinkStore::LinkStore(std::shared_ptr<mysqlx::Client> client) {
    this->client = client;
}

std::vector<Link> LinkStore::getAll() const {
    std::vector<Link> all;
    
    auto session = this->client->getSession();
    
    {
        auto sessionRes = session
        .getDefaultSchema()
        .getTable("links")
        .select("id", "url", "domain", "status", "unix_timestamp(lastCrawlingTime)")
        .execute();
        
        mysqlx::Row row;
        while ((row = sessionRes.fetchOne())) {
            all.push_back(Link((int)row[0], (std::string)row[1], (std::string)row[2], (LinkStatus)(int)row[3], (long long)row[4]));
        }
    }
    
    session.close();
    
    return all;
}

std::optional<Link> LinkStore::getBy(const std::string& url) const {
    auto session = this->client->getSession();
    
    std::optional<Link> link;
    
    {
        auto sessionRes = session
        .getDefaultSchema()
        .getTable("links")
        .select("id", "url", "domain", "status", "unix_timestamp(lastCrawlingTime)")
        .where("url = :url")
        .limit(1)
        .bind("url", url)
        .execute();
        
        mysqlx::Row row;
        if ((row = sessionRes.fetchOne())) {
             link = Link((int)row[0], (std::string)row[1], (std::string)row[2], (LinkStatus)(int)row[3], (long long)row[4]);
        }
    }
    
    session.close();
    
    return link;
}

std::vector<Link> LinkStore::getBy(const std::string& domain, const LinkStatus status, std::size_t count) const {
    std::vector<Link> res;
    
    auto session = this->client->getSession();
    
    {
        auto sessionRes = session
        .getDefaultSchema()
        .getTable("links")
        .select("id", "url", "domain", "status", "unix_timestamp(lastCrawlingTime)")
        .where("status = :status AND domain = :domain")
        .limit(static_cast<unsigned int>(count))
        .bind("status", (int)status)
        .bind("domain", domain)
        .execute();
        
        mysqlx::Row row;
        while ((row = sessionRes.fetchOne())) {
            res.push_back(Link((int)row[0], (std::string)row[1], (std::string)row[2], (LinkStatus)(int)row[3], (long long)row[4]));
        }
    }
    
    session.close();
    
    return res;
}

void LinkStore::add(const Link& link) {
    auto session = this->client->getSession();

    {
        auto res = session.getDefaultSchema()
        .getTable("links")
        .insert("url", "domain", "status")
        .values(link.getUrl(), link.getDomain(), (int)link.getStatus())
        .execute();
    }
    
    session.close();
}

void LinkStore::update(const Link& link) {
    auto session = this->client->getSession();
    
    {
        auto res = session.getDefaultSchema()
        .getTable("links")
        .update()
        .set("domain", link.getDomain())
        .set("status", (int)(link.getStatus()))
        .where("url = :url")
        .bind("url", link.getUrl())
        .execute();
    }
    
    session.close();
}

std::size_t LinkStore::count() const {
    auto session = this->client->getSession();
    
    std::size_t count = 0;
    
    {
        count = session.getDefaultSchema()
        .getTable("links")
        .count();
    }
    
    session.close();
    
    return count;
}
