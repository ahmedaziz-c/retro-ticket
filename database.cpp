#include "database.hpp"
#include <sqlite3.h>
#include <stdexcept>

static sqlite3* g_db = nullptr;

void db::open(const std::string& file)
{
    if (sqlite3_open(file.c_str(), &g_db) != SQLITE_OK)
        throw std::runtime_error("sqlite open");
    sqlite3_exec(g_db,
        "CREATE TABLE IF NOT EXISTS tickets("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "status INTEGER NOT NULL,"
        "created TEXT DEFAULT CURRENT_TIMESTAMP);",
        nullptr, nullptr, nullptr);
}

void db::close()
{
    sqlite3_close(g_db);
}

std::vector<Ticket> db::load_tickets()
{
    std::vector<Ticket> out;
    sqlite3_stmt* st;
    sqlite3_prepare_v2(g_db,
        "SELECT id,title,status,created FROM tickets ORDER BY id;", -1, &st, nullptr);
    while (sqlite3_step(st) == SQLITE_ROW) {
        Ticket t;
        t.id      = sqlite3_column_int(st, 0);
        t.title   = reinterpret_cast<const char*>(sqlite3_column_text(st, 1));
        t.status  = sqlite3_column_int(st, 2);
        t.created = reinterpret_cast<const char*>(sqlite3_column_text(st, 3));
        out.push_back(std::move(t));
    }
    sqlite3_finalize(st);
    return out;
}

int db::insert_ticket(const std::string& title)
{
    sqlite3_stmt* st;
    sqlite3_prepare_v2(g_db,
        "INSERT INTO tickets(title,status) VALUES(?1,0);", -1, &st, nullptr);
    sqlite3_bind_text(st, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(st);
    int newid = static_cast<int>(sqlite3_last_insert_rowid(g_db));
    sqlite3_finalize(st);
    return newid;
}

void db::update_ticket_status(int id, int status)
{
    sqlite3_stmt* st;
    sqlite3_prepare_v2(g_db, "UPDATE tickets SET status=?1 WHERE id=?2;", -1, &st, nullptr);
    sqlite3_bind_int(st, 1, status);
    sqlite3_bind_int(st, 2, id);
    sqlite3_step(st);
    sqlite3_finalize(st);
}