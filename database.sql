CREATE TABLE todos
(
    id INTEGER PRIMARY KEY NOT NULL,
    description TEXT NOT NULL,
    status TEXT NOT NULL,
    priority TEXT NOT NULL,
    due_at TEXT,
    completed_at TEXT,
    created_at TEXT,
    updated_at TEXT
);
