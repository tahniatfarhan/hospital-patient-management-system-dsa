
        function runDSABenchmark() {
            document.getElementById('demoBody').innerHTML = `
                <div>$ ./hospital_dsa_benchmark</div>
                <div style="color: #4ade80; margin-top: 8px;">Inserting 10,000 Patient Records (Sorted Input)...</div>
                <div style="color: #f59e0b;">Standard BST Time: 18.4 ms (Degraded to O(N) Unbalanced Tree)</div>
                <div style="color: #4ade80;">AVL Tree Time:    0.82 ms (Balanced O(log N) via Left-Right Rotations)</div>
                <div style="color: #e2e8f0; margin-top: 8px;">[RAII DESTRUCTOR] Cleaned up 10,000 nodes via post-order traversal (0 memory leaks).</div>
            `;
        }
        document.getElementById('demoBody').innerHTML = `
            <div>
                <button class="term-btn" onclick="runDSABenchmark()">Run BST vs AVL Benchmark</button>
            </div>
            <div>$ Click button to execute C++ DSA benchmark visualizer...</div>
        `;
        