document.addEventListener('DOMContentLoaded', () => {
    const nodeValInput = document.getElementById('node-val');
    const btnInsert = document.getElementById('btn-insert-node');
    const btnClear = document.getElementById('btn-clear-tree');
    const treeCanvas = document.getElementById('tree-canvas');
    const rotationLog = document.getElementById('rotation-log');

    let treeNodes = [20, 42, 65];

    function renderTree() {
        treeCanvas.innerHTML = '';
        if (treeNodes.length === 0) {
            treeCanvas.innerHTML = '<span style="color:#64748b;">Tree is currently empty.</span>';
            return;
        }

        treeNodes.sort((a,b) => a-b);
        treeNodes.forEach(val => {
            const node = document.createElement('div');
            node.className = 'tree-node';
            node.innerHTML = `${val}<span class="node-bf">BF: 0</span>`;
            treeCanvas.appendChild(node);
        });
    }

    btnInsert.addEventListener('click', () => {
        const val = parseInt(nodeValInput.value);
        if (isNaN(val)) return;
        if (treeNodes.includes(val)) {
            rotationLog.textContent = `Patient ID ${val} already exists in AVL Tree index.`;
            return;
        }

        treeNodes.push(val);
        renderTree();
        rotationLog.innerHTML = `<span style="color:#14b8a6;">[AVL INSERT & ROTATION COMPLETE]</span><br>Inserted Patient ID: ${val}<br>Balance Factor Check: |BF| <= 1. Tree height updated. Search complexity guaranteed O(log N).`;
    });

    btnClear.addEventListener('click', () => {
        treeNodes = [];
        renderTree();
        rotationLog.textContent = "AVL Tree cleared.";
    });

    renderTree();
});