#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <sstream>

#include "WebsiteStore.hpp"
#include "Website.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

WebsiteStore::WebsiteStore(std::shared_ptr<mysqlx::Client> client) {
    this->client = client;
}

std::vector<Website> WebsiteStore::getAll() const {
    std::vector<Website> all;
    
    auto session = this->client->getSession();
    
    {
        auto sessionRes = session
        .getDefaultSchema()
        .getTable("websites")
        .select("id", "domain", "homepage", "unix_timestamp(lastCrawlingTime)")
        .execute();
        
        mysqlx::Row row;
        while ((row = sessionRes.fetchOne())) {
            all.push_back(Website((int)row[0], (std::string)row[1], (std::string)row[2], (long long)row[3]));
        }
    }
    
    session.close();
    
    return all;
}

void WebsiteStore::add(const Website& website) {
    auto session = this->client->getSession();
    
    {
        auto res = session.getDefaultSchema()
        .getTable("websites")
        .insert("domain", "homepage")
        .values(website.getDomain(), website.getHomepage())
        .execute();
    }
    
    session.close();
}

static std::string getDateLocalTime(long timestamp) {
    std::stringstream dateStr;
    
    boost::posix_time::ptime pt_1 = boost::posix_time::from_time_t(timestamp);
    
    boost::gregorian::date d = pt_1.date();
    
    auto td = pt_1.time_of_day();
    
    // construct the Date Time string
    dateStr << d.year() << "-" << std::setw(2) << std::setfill('0') << d.month().as_number() << "-" << std::setw(2) << std::setfill('0') << d.day() << " " << td.hours() << ":" << td.minutes() << ":" << td.seconds();
    
    return dateStr.str();
}

void WebsiteStore::update(const Website& website) {
    auto session = this->client->getSession();
    
    {
        auto res = session.getDefaultSchema()
        .getTable("websites")
        .update()
        .set("domain", website.getDomain())
        .set("homepage", website.getHomepage())
        .set("lastCrawlingTime", getDateLocalTime(website.getLastCrawlingTime()))
        .where("id = :id")
        .bind("id", website.getId())
        .execute();
    }
    
    session.close();
}
