// TODO List Application
class TodoApp {
    constructor() {
        this.todos = this.loadTodos();
        this.currentFilter = 'all';
        this.editingId = null;
        this.init();
    }

    init() {
        this.renderTodos();
        this.updateStats();
        this.setupEventListeners();
    }

    setupEventListeners() {
        const todoInput = document.getElementById('todoInput');
        const addBtn = document.getElementById('addBtn');

        // Add todo on Enter key press
        todoInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.addTodo();
            }
        });

        // Add todo on button click
        addBtn.addEventListener('click', () => this.addTodo());
    }

    loadTodos() {
        const saved = localStorage.getItem('todos');
        return saved ? JSON.parse(saved) : [];
    }

    saveTodos() {
        localStorage.setItem('todos', JSON.stringify(this.todos));
    }

    generateId() {
        return Date.now() + Math.random().toString(36).substr(2, 9);
    }

    addTodo() {
        const input = document.getElementById('todoInput');
        const text = input.value.trim();

        if (!text) {
            this.showNotification('Please enter a task!', 'error');
            return;
        }

        if (this.editingId) {
            // Update existing todo
            const todo = this.todos.find(t => t.id === this.editingId);
            if (todo) {
                todo.text = text;
                todo.updatedAt = new Date().toISOString();
                this.editingId = null;
                document.getElementById('addBtn').innerHTML = '<i class="fas fa-plus"></i> Add';
                this.showNotification('Task updated successfully!', 'success');
            }
        } else {
            // Add new todo
            const newTodo = {
                id: this.generateId(),
                text: text,
                completed: false,
                createdAt: new Date().toISOString(),
                updatedAt: new Date().toISOString()
            };
            this.todos.unshift(newTodo);
            this.showNotification('Task added successfully!', 'success');
        }

        input.value = '';
        this.saveTodos();
        this.renderTodos();
        this.updateStats();
    }

    deleteTodo(id) {
        const todoElement = document.querySelector(`[data-id="${id}"]`);
        if (todoElement) {
            todoElement.classList.add('removing');
            setTimeout(() => {
                this.todos = this.todos.filter(todo => todo.id !== id);
                this.saveTodos();
                this.renderTodos();
                this.updateStats();
                this.showNotification('Task deleted!', 'success');
            }, 300);
        }
    }

    editTodo(id) {
        const todo = this.todos.find(t => t.id === id);
        if (todo) {
            const input = document.getElementById('todoInput');
            input.value = todo.text;
            input.focus();
            this.editingId = id;
            document.getElementById('addBtn').innerHTML = '<i class="fas fa-save"></i> Update';
        }
    }

    toggleTodo(id) {
        const todo = this.todos.find(t => t.id === id);
        if (todo) {
            todo.completed = !todo.completed;
            todo.updatedAt = new Date().toISOString();
            this.saveTodos();
            this.renderTodos();
            this.updateStats();
            
            const message = todo.completed ? 'Task completed!' : 'Task marked as active!';
            this.showNotification(message, 'success');
        }
    }

    filterTodos(filter) {
        this.currentFilter = filter;
        
        // Update filter buttons
        document.querySelectorAll('.filter-btn').forEach(btn => {
            btn.classList.remove('active');
        });
        event.target.classList.add('active');
        
        this.renderTodos();
    }

    getFilteredTodos() {
        switch (this.currentFilter) {
            case 'active':
                return this.todos.filter(todo => !todo.completed);
            case 'completed':
                return this.todos.filter(todo => todo.completed);
            default:
                return this.todos;
        }
    }

    renderTodos() {
        const todoList = document.getElementById('todoList');
        const emptyState = document.getElementById('emptyState');
        const filteredTodos = this.getFilteredTodos();

        if (filteredTodos.length === 0) {
            todoList.style.display = 'none';
            emptyState.classList.add('show');
            
            // Update empty state message based on filter
            const emptyMessage = emptyState.querySelector('p');
            switch (this.currentFilter) {
                case 'active':
                    emptyMessage.textContent = 'No active tasks! Great job!';
                    break;
                case 'completed':
                    emptyMessage.textContent = 'No completed tasks yet.';
                    break;
                default:
                    emptyMessage.textContent = 'Add your first task above to get started!';
            }
        } else {
            todoList.style.display = 'block';
            emptyState.classList.remove('show');
        }

        todoList.innerHTML = filteredTodos.map(todo => `
            <li class="todo-item ${todo.completed ? 'completed' : ''}" data-id="${todo.id}">
                <div class="todo-checkbox ${todo.completed ? 'checked' : ''}" 
                     onclick="todoApp.toggleTodo('${todo.id}')"></div>
                <div class="todo-text">${this.escapeHtml(todo.text)}</div>
                <div class="todo-actions">
                    <button class="edit-btn" onclick="todoApp.editTodo('${todo.id}')" 
                            title="Edit task">
                        <i class="fas fa-edit"></i>
                    </button>
                    <button class="delete-btn" onclick="todoApp.deleteTodo('${todo.id}')" 
                            title="Delete task">
                        <i class="fas fa-trash"></i>
                    </button>
                </div>
            </li>
        `).join('');

        // Update clear completed button state
        const clearBtn = document.getElementById('clearCompleted');
        const hasCompleted = this.todos.some(todo => todo.completed);
        clearBtn.disabled = !hasCompleted;
    }

    updateStats() {
        const totalCount = document.getElementById('totalCount');
        const completedCount = document.getElementById('completedCount');
        
        const total = this.todos.length;
        const completed = this.todos.filter(todo => todo.completed).length;
        
        totalCount.textContent = `${total} ${total === 1 ? 'task' : 'tasks'}`;
        completedCount.textContent = `${completed} completed`;
    }

    clearCompleted() {
        const completedTodos = this.todos.filter(todo => todo.completed);
        if (completedTodos.length === 0) return;

        if (confirm(`Are you sure you want to delete ${completedTodos.length} completed task(s)?`)) {
            this.todos = this.todos.filter(todo => !todo.completed);
            this.saveTodos();
            this.renderTodos();
            this.updateStats();
            this.showNotification(`${completedTodos.length} completed task(s) deleted!`, 'success');
        }
    }

    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }

    showNotification(message, type = 'info') {
        // Create notification element
        const notification = document.createElement('div');
        notification.className = `notification ${type}`;
        notification.textContent = message;
        
        // Add styles
        Object.assign(notification.style, {
            position: 'fixed',
            top: '20px',
            right: '20px',
            padding: '12px 20px',
            borderRadius: '8px',
            color: 'white',
            fontWeight: '500',
            zIndex: '1000',
            transform: 'translateX(400px)',
            transition: 'transform 0.3s ease',
            maxWidth: '300px',
            wordWrap: 'break-word'
        });

        // Set background color based on type
        switch (type) {
            case 'success':
                notification.style.background = '#28a745';
                break;
            case 'error':
                notification.style.background = '#dc3545';
                break;
            default:
                notification.style.background = '#6c757d';
        }

        document.body.appendChild(notification);

        // Animate in
        setTimeout(() => {
            notification.style.transform = 'translateX(0)';
        }, 100);

        // Animate out and remove
        setTimeout(() => {
            notification.style.transform = 'translateX(400px)';
            setTimeout(() => {
                document.body.removeChild(notification);
            }, 300);
        }, 3000);
    }
}

// Global functions for HTML onclick handlers
let todoApp;

function addTodo() {
    todoApp.addTodo();
}

function filterTodos(filter) {
    todoApp.filterTodos(filter);
}

function clearCompleted() {
    todoApp.clearCompleted();
}

// Initialize the app when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    todoApp = new TodoApp();
});

// Add some sample todos on first visit
document.addEventListener('DOMContentLoaded', () => {
    const hasVisited = localStorage.getItem('hasVisited');
    if (!hasVisited) {
        setTimeout(() => {
            const sampleTodos = [
                'Welcome to your TODO list! 🎉',
                'Click the checkbox to mark tasks as complete',
                'Use the edit button to modify tasks',
                'Try the filter buttons to view different task types'
            ];
            
            sampleTodos.forEach((text, index) => {
                const todo = {
                    id: todoApp.generateId(),
                    text: text,
                    completed: index === 1, // Mark second item as completed
                    createdAt: new Date().toISOString(),
                    updatedAt: new Date().toISOString()
                };
                todoApp.todos.push(todo);
            });
            
            todoApp.saveTodos();
            todoApp.renderTodos();
            todoApp.updateStats();
            
            localStorage.setItem('hasVisited', 'true');
        }, 500);
    }
});